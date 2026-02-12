static int lz4_wrap_compress(const char* input, size_t input_length,
                             char* output, size_t maxout, int accel, void* hash_table) {
  BLOSC_UNUSED_PARAM(accel);
  int cbytes;
#ifdef HAVE_IPP
  if (hash_table == NULL) {
    return -1;
  }
  int outlen = (int)maxout;
  int inlen = (int)input_length;


  IppStatus status = ippsEncodeLZ4Safe_8u((const Ipp8u*)input, &inlen,
                                           (Ipp8u*)output, &outlen, (Ipp8u*)hash_table);
  if (status == ippStsDstSizeLessExpected) {
    return 0;
  }
  else if (status != ippStsNoErr) {
    return -1;
  }
  cbytes = outlen;
#else
  BLOSC_UNUSED_PARAM(hash_table);
  accel = 1;
  cbytes = LZ4_compress_fast(input, output, (int)input_length, (int)maxout, accel);
#endif
  return cbytes;
}
