const char* blosc_cbuffer_complib(const void* cbuffer) {
  uint8_t* _src = (uint8_t*)(cbuffer);
  int clibcode;
  const char* complib;


  clibcode = (_src[2] & 0xe0) >> 5;
  complib = clibcode_to_clibname(clibcode);
  return complib;
}
