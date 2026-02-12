void blosc_cbuffer_versions(const void* cbuffer, int* version,
                            int* versionlz) {
  uint8_t* _src = (uint8_t*)(cbuffer);


  *version = (int)_src[0];
  *versionlz = (int)_src[1];
}
