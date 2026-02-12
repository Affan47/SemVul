bool PesHeader::Write(bool write_pts, PacketDataBuffer* buffer) const {
  if (buffer == nullptr) {
    std::fprintf(stderr, "Webm2Pes: nullptr in header writer.\n");
    return false;
  }


  const int kStartCodeLength = 4;
  for (int i = 0; i < kStartCodeLength; ++i)
    buffer->push_back(start_code[i]);


  const std::size_t header_length =
      packet_length + optional_header.size_in_bytes();
  if (header_length > UINT16_MAX)
    return false;


  std::uint8_t byte = (header_length >> 8) & 0xff;
  buffer->push_back(byte);
  byte = header_length & 0xff;
  buffer->push_back(byte);


  if (optional_header.Write(write_pts, buffer) != true) {
    std::fprintf(stderr, "Webm2Pes: PES optional header write failed.");
    return false;
  }
  return true;
}
