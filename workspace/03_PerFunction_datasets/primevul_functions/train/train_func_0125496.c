bool PesOptionalHeader::Write(bool write_pts, PacketDataBuffer* buffer) const {
  if (buffer == nullptr) {
    std::fprintf(stderr, "Webm2Pes: nullptr in opt header writer.\n");
    return false;
  }

  const int kHeaderSize = 9;
  std::uint8_t header[kHeaderSize] = {0};
  std::uint8_t* byte = header;

  if (marker.Check() != true || scrambling.Check() != true ||
      priority.Check() != true || data_alignment.Check() != true ||
      copyright.Check() != true || original.Check() != true ||
      has_pts.Check() != true || has_dts.Check() != true ||
      pts.Check() != true || stuffing_byte.Check() != true) {
    std::fprintf(stderr, "Webm2Pes: Invalid PES Optional Header field.\n");
    return false;
  }


  *byte = 0;
  *byte |= marker.bits << marker.shift;
  *byte |= scrambling.bits << scrambling.shift;
  *byte |= priority.bits << priority.shift;
  *byte |= data_alignment.bits << data_alignment.shift;
  *byte |= copyright.bits << copyright.shift;
  *byte |= original.bits << original.shift;


  *++byte = 0;
  if (write_pts == true)
    *byte |= has_pts.bits << has_pts.shift;

  *byte |= has_dts.bits << has_dts.shift;


  *++byte = remaining_size.bits & 0xff;

  int num_stuffing_bytes =
      (pts.num_bits + 7) / 8 + 1 ;
  if (write_pts == true) {


    *++byte = pts.bits & 0xff;
    *++byte = (pts.bits >> 8) & 0xff;
    *++byte = (pts.bits >> 16) & 0xff;
    *++byte = (pts.bits >> 24) & 0xff;
    *++byte = (pts.bits >> 32) & 0xff;
    num_stuffing_bytes = 1;
  }


  for (int i = 0; i < num_stuffing_bytes; ++i)
    *++byte = stuffing_byte.bits & 0xff;

  return CopyAndEscapeStartCodes(&header[0], kHeaderSize, buffer);
}
