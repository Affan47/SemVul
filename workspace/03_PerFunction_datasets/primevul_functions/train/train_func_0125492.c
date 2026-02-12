void PesOptionalHeader::SetPtsBits(std::int64_t pts_90khz) {
  std::uint64_t* pts_bits = &pts.bits;
  *pts_bits = 0;


  const std::uint32_t pts1 = (pts_90khz >> 30) & 0x7;
  const std::uint32_t pts2 = (pts_90khz >> 15) & 0x7FFF;
  const std::uint32_t pts3 = pts_90khz & 0x7FFF;

  std::uint8_t buffer[5] = {0};

  buffer[0] |= 1 << 5;

  buffer[0] |= pts1 << 1;

  buffer[0] |= 1;


  buffer[1] |= (pts2 >> 7) & 0xff;

  buffer[2] |= (pts2 << 1);

  buffer[2] |= 1;


  buffer[3] |= (pts3 >> 7) & 0xff;

  buffer[4] |= (pts3 << 1);

  buffer[4] |= 1;


  std::memcpy(reinterpret_cast<std::uint8_t*>(pts_bits), buffer, 5);
}
