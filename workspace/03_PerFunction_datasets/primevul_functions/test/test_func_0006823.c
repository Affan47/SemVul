static FP32 half_to_float(FP16 h) {
  static const FP32 magic = {113 << 23};
  static const unsigned int shifted_exp = 0x7c00
                                          << 13;
  FP32 o;

  o.u = (h.u & 0x7fffU) << 13U;
  unsigned int exp_ = shifted_exp & o.u;
  o.u += (127 - 15) << 23;


  if (exp_ == shifted_exp)
    o.u += (128 - 16) << 23;
  else if (exp_ == 0)
  {
    o.u += 1 << 23;
    o.f -= magic.f;
  }

  o.u |= (h.u & 0x8000U) << 16U;
  return o;
}
