int blosc_cbuffer_validate(const void* cbuffer, size_t cbytes, size_t* nbytes) {
  size_t header_cbytes, header_blocksize;
  if (cbytes < BLOSC_MIN_HEADER_LENGTH) {

    *nbytes = 0;
    return -1;
  }
  blosc_cbuffer_sizes(cbuffer, nbytes, &header_cbytes, &header_blocksize);
  if (header_cbytes != cbytes) {

    *nbytes = 0;
    return -1;
  }
  if (*nbytes > BLOSC_MAX_BUFFERSIZE) {

    return -1;
  }
  return 0;
}
