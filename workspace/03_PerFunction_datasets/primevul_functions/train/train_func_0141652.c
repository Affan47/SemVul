Fraction::Fraction(int32_t num,int32_t den)
{


  while (denominator > MAX_FRACTION_VALUE || denominator < -MAX_FRACTION_VALUE) {
    numerator /= 2;
    denominator /= 2;
  }

  while (numerator > MAX_FRACTION_VALUE || numerator < -MAX_FRACTION_VALUE) {
    numerator /= 2;
    denominator /= 2;
  }
}
