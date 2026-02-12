uint8_t APar_ExtractChannelInfo(FILE *isofile, uint32_t pos) {
  uint8_t packed_channels = APar_read8(isofile, pos);
  uint8_t unpacked_channels =
      (packed_channels << 1);
  unpacked_channels =
      (unpacked_channels >> 4);
  return unpacked_channels;
}
