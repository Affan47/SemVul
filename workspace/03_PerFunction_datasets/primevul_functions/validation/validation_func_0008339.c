void blosc_cbuffer_metainfo(const void* cbuffer, size_t* typesize, int* flags) {
  uint8_t* _src = (uint8_t*)(cbuffer);
  uint8_t version = _src[0];
  if (version > BLOSC_VERSION_FORMAT) {

    *flags = 0;
    *typesize = 0;
    return;
  }


  *flags = (int)_src[2];
  *typesize = (size_t)_src[3];
}
