SubtractGreenFromBlueAndRed(uint32_t* argb_data, int num_pixs) {
  int i = 0;
  for (; i < num_pixs; ++i) {
    const uint32_t argb = argb_data[i];
    const uint32_t green = (argb >> 8) & 0xff;
    const uint32_t new_r = (((argb >> 16) & 0xff) - green) & 0xff;
    const uint32_t new_b = ((argb & 0xff) - green) & 0xff;
    argb_data[i] = (argb & 0xff00ff00) | (new_r << 16) | new_b;
  }
}
