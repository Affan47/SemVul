inline int32_t MultiplyByQuantizedMultiplier(int64_t x,
                                             int32_t quantized_multiplier,
                                             int shift) {


  assert(quantized_multiplier >= 0);
  assert(shift >= -31 && shift < 8);
  assert(x >= -(static_cast<int64_t>(1) << 47) &&
         x < (static_cast<int64_t>(1) << 47));

  int32_t reduced_multiplier = (quantized_multiplier < 0x7FFF0000)
                                   ? ((quantized_multiplier + (1 << 15)) >> 16)
                                   : 0x7FFF;
  int total_shift = 15 - shift;
  x = (x * (int64_t)reduced_multiplier) + ((int64_t)1 << (total_shift - 1));
  int32_t result = x >> total_shift;
  return result;
}
