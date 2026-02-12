static int initialize_context_decompression(blosc2_context* context, const void* src, int32_t srcsize,
                                            void* dest, int32_t destsize) {
  uint8_t blosc2_flags = 0;
  int32_t cbytes;
  int32_t bstarts_offset;
  int32_t bstarts_end;

  context->do_compress = 0;
  context->src = (const uint8_t*)src;
  context->srcsize = srcsize;
  context->dest = (uint8_t*)dest;
  context->destsize = destsize;
  context->output_bytes = 0;
  context->end_threads = 0;

  if (context->srcsize < BLOSC_MIN_HEADER_LENGTH) {

    return -1;
  }

  context->header_flags = context->src[2];
  context->typesize = context->src[3];
  context->sourcesize = sw32_(context->src + 4);
  context->blocksize = sw32_(context->src + 8);
  cbytes = sw32_(context->src + 12);


  if (context->blocksize <= 0 || context->blocksize > destsize ||
      context->typesize <= 0 || context->typesize > BLOSC_MAX_TYPESIZE ||
      cbytes > srcsize) {
    return -1;
  }

  if (context->sourcesize > (int32_t)destsize) {
    return -1;
  }


  context->nblocks = context->sourcesize / context->blocksize;
  context->leftover = context->sourcesize % context->blocksize;
  context->nblocks = (context->leftover > 0) ?
                      context->nblocks + 1 : context->nblocks;

  if (context->block_maskout != NULL && context->block_maskout_nitems != context->nblocks) {
    fprintf(stderr, "The number of items in block_maskout (%d) must match the number"
                    " of blocks in chunk (%d)", context->block_maskout_nitems, context->nblocks);
    return -2;
  }

  if ((context->header_flags & BLOSC_DOSHUFFLE) &&
      (context->header_flags & BLOSC_DOBITSHUFFLE)) {

    if (context->srcsize < BLOSC_EXTENDED_HEADER_LENGTH) {

      return -1;
    }
    uint8_t* filters = (uint8_t*)(context->src + BLOSC_MIN_HEADER_LENGTH);
    uint8_t* filters_meta = filters + 8;
    uint8_t header_version = context->src[0];


    int max_filters = (header_version == BLOSC2_VERSION_FORMAT_ALPHA) ? 5 : BLOSC2_MAX_FILTERS;
    for (int i = 0; i < max_filters; i++) {
      context->filters[i] = filters[i];
      context->filters_meta[i] = filters_meta[i];
    }
    context->filter_flags = filters_to_flags(filters);
    bstarts_offset = BLOSC_EXTENDED_HEADER_LENGTH;
    blosc2_flags = context->src[0x1F];
  } else {

    context->filter_flags = get_filter_flags(context->header_flags,
                                             context->typesize);
    flags_to_filters(context->header_flags, context->filters);
    bstarts_offset = BLOSC_MIN_HEADER_LENGTH;
  }

  context->bstarts = (int32_t*)(context->src + bstarts_offset);
  bstarts_end = bstarts_offset + (context->nblocks * sizeof(int32_t));
  if (srcsize < bstarts_end) {

    return -1;
  }
  srcsize -= bstarts_end;


  if (blosc2_flags & BLOSC2_USEDICT) {
#if defined(HAVE_ZSTD)
    context->use_dict = 1;
    if (context->dict_ddict != NULL) {

      ZSTD_freeDDict(context->dict_ddict);
    }

    if (srcsize < sizeof(int32_t)) {

      return -1;
    }
    srcsize -= sizeof(int32_t);
    context->dict_size = (size_t)sw32_(context->src + bstarts_end);
    if (context->dict_size <= 0 || context->dict_size > BLOSC2_MAXDICTSIZE) {

      return -1;
    }
    if (srcsize < (int32_t)context->dict_size) {

      return -1;
    }
    srcsize -= context->dict_size;
    context->dict_buffer = (void*)(context->src + bstarts_end + sizeof(int32_t));
    context->dict_ddict = ZSTD_createDDict(context->dict_buffer, context->dict_size);
#endif
  }


  return 0;
}
