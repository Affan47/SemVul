WriteUInt32(uint32 val) {
  uint32 v = (byte_order_ == ORDER_NETWORK) ? HostToNetwork32(val) : val;
  WriteBytes(reinterpret_cast<const char*>(&v), 4);
}
