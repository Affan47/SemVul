static int serial_blosc(struct thread_context* thread_context) {
  blosc2_context* context = thread_context->parent_context;
  int32_t j, bsize, leftoverblock;
  int32_t cbytes;
  int32_t ntbytes = (int32_t)context->output_bytes;
  int32_t* bstarts = context->bstarts;
  uint8_t* tmp = thread_context->tmp;
  uint8_t* tmp2 = thread_context->tmp2;
  int dict_training = context->use_dict && (context->dict_cdict == NULL);
  bool memcpyed = context->header_flags & (uint8_t)BLOSC_MEMCPYED;

  for (j = 0; j < context->nblocks; j++) {
    if (context->do_compress && !memcpyed && !dict_training) {
      _sw32(bstarts + j, ntbytes);
    }
    bsize = context->blocksize;
    leftoverblock = 0;
    if ((j == context->nblocks - 1) && (context->leftover > 0)) {
      bsize = context->leftover;
      leftoverblock = 1;
    }
    if (context->do_compress) {
      if (memcpyed && !context->prefilter) {

        memcpy(context->dest + BLOSC_MAX_OVERHEAD + j * context->blocksize,
                 context->src + j * context->blocksize,
                 (unsigned int)bsize);
        cbytes = (int32_t)bsize;
      }
      else {

        cbytes = blosc_c(thread_context, bsize, leftoverblock, ntbytes,
                         context->destsize, context->src, j * context->blocksize,
                         context->dest + ntbytes, tmp, tmp2);
        if (cbytes == 0) {
          ntbytes = 0;
          break;
        }
      }
    }
    else {
      if (memcpyed) {

        int32_t csize = sw32_(context->src + 12);
        if (context->sourcesize + BLOSC_MAX_OVERHEAD != csize) {
          return -1;
        }
        if (context->srcsize < BLOSC_MAX_OVERHEAD + (j * context->blocksize) + bsize) {

          return -1;
        }
        memcpy(context->dest + j * context->blocksize,
               context->src + BLOSC_MAX_OVERHEAD + j * context->blocksize,
               (unsigned int)bsize);
        cbytes = (int32_t)bsize;
      }
      else {

        cbytes = blosc_d(thread_context, bsize, leftoverblock,
                         context->src, context->srcsize, sw32_(bstarts + j),
                         context->dest, j * context->blocksize, tmp, tmp2);
      }
    }

    if (cbytes < 0) {
      ntbytes = cbytes;
      break;
    }
    ntbytes += cbytes;
  }

  return ntbytes;
}
