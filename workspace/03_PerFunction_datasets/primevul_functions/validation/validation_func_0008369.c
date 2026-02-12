void blosc_cbuffer_sizes(const void* cbuffer, size_t* nbytes,
                         size_t* cbytes, size_t* blocksize) {
  uint8_t* _src = (uint8_t*)(cbuffer);
  uint8_t version = _src[0];
  if (version > BLOSC_VERSION_FORMAT) {

    *nbytes = *blocksize = *cbytes = 0;
    return;
  }


  *nbytes = (size_t)sw32_(_src + 4);
  *blocksize = (size_t)sw32_(_src + 8);
  *cbytes = (size_t)sw32_(_src + 12);
}
