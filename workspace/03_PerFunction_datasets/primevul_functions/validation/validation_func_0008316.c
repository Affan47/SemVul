static void t_blosc_do_job(void *ctxt)
{
  struct thread_context* thcontext = (struct thread_context*)ctxt;
  blosc2_context* context = thcontext->parent_context;
  int32_t cbytes;
  int32_t ntdest;
  int32_t tblocks;
  int32_t tblock;
  int32_t nblock_;
  int32_t bsize;
  int32_t leftoverblock;

  int32_t blocksize;
  int32_t ebsize;
  int32_t srcsize;
  bool compress = context->do_compress != 0;
  int32_t maxbytes;
  int32_t nblocks;
  int32_t leftover;
  int32_t leftover2;
  int32_t* bstarts;
  const uint8_t* src;
  uint8_t* dest;
  uint8_t* tmp;
  uint8_t* tmp2;
  uint8_t* tmp3;


  blocksize = context->blocksize;
  ebsize = blocksize + context->typesize * sizeof(int32_t);
  maxbytes = context->destsize;
  nblocks = context->nblocks;
  leftover = context->leftover;
  bstarts = context->bstarts;
  src = context->src;
  srcsize = context->srcsize;
  dest = context->dest;


  if (blocksize != thcontext->tmp_blocksize) {
    my_free(thcontext->tmp);
    thcontext->tmp_nbytes = (size_t)3 * context->blocksize + ebsize;
    thcontext->tmp = my_malloc(thcontext->tmp_nbytes);
    thcontext->tmp2 = thcontext->tmp + blocksize;
    thcontext->tmp3 = thcontext->tmp + blocksize + ebsize;
    thcontext->tmp4 = thcontext->tmp + 2 * blocksize + ebsize;
    thcontext->tmp_blocksize = blocksize;
  }

  tmp = thcontext->tmp;
  tmp2 = thcontext->tmp2;
  tmp3 = thcontext->tmp3;


  bool memcpyed = context->header_flags & (uint8_t)BLOSC_MEMCPYED;
  bool static_schedule = (!compress || memcpyed) && context->block_maskout == NULL;
  if (static_schedule) {

      tblocks = nblocks / context->nthreads;
      leftover2 = nblocks % context->nthreads;
      tblocks = (leftover2 > 0) ? tblocks + 1 : tblocks;
      nblock_ = thcontext->tid * tblocks;
      tblock = nblock_ + tblocks;
      if (tblock > nblocks) {
          tblock = nblocks;
      }
  }
  else {

    pthread_mutex_lock(&context->count_mutex);
    context->thread_nblock++;
    nblock_ = context->thread_nblock;
    pthread_mutex_unlock(&context->count_mutex);
    tblock = nblocks;
  }


  leftoverblock = 0;
  while ((nblock_ < tblock) && (context->thread_giveup_code > 0)) {
    bsize = blocksize;
    if (nblock_ == (nblocks - 1) && (leftover > 0)) {
      bsize = leftover;
      leftoverblock = 1;
    }
    if (compress) {
      if (memcpyed) {
        if (!context->prefilter) {

          memcpy(dest + BLOSC_MAX_OVERHEAD + nblock_ * blocksize,
                 src + nblock_ * blocksize, (unsigned int) bsize);
          cbytes = (int32_t) bsize;
        }
        else {


          cbytes = blosc_c(thcontext, bsize, leftoverblock, 0,
                           ebsize, src, nblock_ * blocksize,
                           dest + BLOSC_MAX_OVERHEAD + nblock_ * blocksize,
                           tmp, tmp3);
        }
      }
      else {

        cbytes = blosc_c(thcontext, bsize, leftoverblock, 0,
                          ebsize, src, nblock_ * blocksize, tmp2, tmp, tmp3);
      }
    }
    else {
      if (memcpyed) {

        if (srcsize < BLOSC_MAX_OVERHEAD + (nblock_ * blocksize) + bsize) {


          cbytes = -1;
        } else {
          memcpy(dest + nblock_ * blocksize,
                  src + BLOSC_MAX_OVERHEAD + nblock_ * blocksize, (unsigned int)bsize);
          cbytes = (int32_t)bsize;
        }
      }
      else {
        if (srcsize < (int32_t)(BLOSC_MAX_OVERHEAD + (sizeof(int32_t) * nblocks))) {

          cbytes = -1;
        } else {
          cbytes = blosc_d(thcontext, bsize, leftoverblock,
                            src, srcsize, sw32_(bstarts + nblock_),
                            dest, nblock_ * blocksize, tmp, tmp2);
        }
      }
    }


    if (context->thread_giveup_code <= 0) {
      break;
    }


    if (cbytes < 0) {

      pthread_mutex_lock(&context->count_mutex);
      context->thread_giveup_code = cbytes;
      pthread_mutex_unlock(&context->count_mutex);
      break;
    }

    if (compress && !memcpyed) {

      pthread_mutex_lock(&context->count_mutex);
      ntdest = context->output_bytes;


      if (!(context->use_dict && context->dict_cdict == NULL)) {
        _sw32(bstarts + nblock_, (int32_t) ntdest);
      }

      if ((cbytes == 0) || (ntdest + cbytes > maxbytes)) {
        context->thread_giveup_code = 0;
        pthread_mutex_unlock(&context->count_mutex);
        break;
      }
      context->thread_nblock++;
      nblock_ = context->thread_nblock;
      context->output_bytes += cbytes;
      pthread_mutex_unlock(&context->count_mutex);


      memcpy(dest + ntdest, tmp2, (unsigned int) cbytes);
    }
    else if (static_schedule) {
      nblock_++;
    }
    else {
      pthread_mutex_lock(&context->count_mutex);
      context->thread_nblock++;
      nblock_ = context->thread_nblock;
      context->output_bytes += cbytes;
      pthread_mutex_unlock(&context->count_mutex);
    }

  }

  if (static_schedule) {
    context->output_bytes = context->sourcesize;
    if (compress) {
      context->output_bytes += BLOSC_MAX_OVERHEAD;
    }
  }

}
