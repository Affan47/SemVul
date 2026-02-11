constRHSGrayShadow(const Rational& c,
						  const Rational& b,
						  const Rational& a) {
  DebugAssert(c.isInteger() &&
	      b.isInteger() &&
	      a.isInteger() &&
	      b != 0,
	      "ArithTheoremProducer::constRHSGrayShadow: a, b, c must be ints");
  if (b > 0)
    return mod(c+b, a);
  else
    return mod(a-(c+b), a);
}
