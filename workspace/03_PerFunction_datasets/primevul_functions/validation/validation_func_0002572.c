PrimitiveStatus FinalizeEnclave(void *context, MessageReader *in,
                                MessageWriter *out) {
  if (in) {
    ASYLO_RETURN_IF_READER_NOT_EMPTY(*in);
  }


  delete UntrustedCacheMalloc::Instance();
  return asylo_enclave_fini();
}
