uint64_t InstanceKlass::get_stored_fingerprint() const {
  address adr = adr_fingerprint();
  if (adr != NULL) {
    return (uint64_t)Bytes::get_native_u8(adr);
  }
  return 0;
}
