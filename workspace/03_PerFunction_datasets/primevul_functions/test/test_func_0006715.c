static FP16 float_to_half_full(FP32 f) {
  FP16 o = {0};


  if (f.s.Exponent == 0)
    o.s.Exponent = 0;
  else if (f.s.Exponent == 255)
  {
    o.s.Exponent = 31;
    o.s.Mantissa = f.s.Mantissa ? 0x200 : 0;
  } else
  {

    int newexp = f.s.Exponent - 127 + 15;
    if (newexp >= 31)
      o.s.Exponent = 31;
    else if (newexp <= 0)
    {
      if ((14 - newexp) <= 24)
      {
        unsigned int mant = f.s.Mantissa | 0x800000;
        o.s.Mantissa = mant >> (14 - newexp);
        if ((mant >> (13 - newexp)) & 1)
          o.u++;
      }
    } else {
      o.s.Exponent = static_cast<unsigned int>(newexp);
      o.s.Mantissa = f.s.Mantissa >> 13;
      if (f.s.Mantissa & 0x1000)
        o.u++;
    }
  }

  o.s.Sign = f.s.Sign;
  return o;
}
