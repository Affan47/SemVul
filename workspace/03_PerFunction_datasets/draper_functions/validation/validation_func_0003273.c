BlockCRC16(byte *block, uint32 len) {
  uint16 crc;
  uint32 i, indx;

  crc = CRC16_INIT;
  for (i = 0; i < len; i++) {
    indx = (uint8)(*block++ ^ crc);
    crc >>= 8;
    crc ^= CRC16Table[indx];
  }
  return crc;
}
