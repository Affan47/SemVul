libpd_polyaftertouch(int channel, int pitch, int value) {
  CHECK_CHANNEL
  CHECK_RANGE_7BIT(pitch)
  CHECK_RANGE_7BIT(value)
  inmidi_polyaftertouch(PORT, CHANNEL, pitch, value);
  return 0;
}
