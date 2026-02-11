Modulo(const PolynomialMod2 &b) const
{
	PolynomialMod2 remainder, quotient;
	PolynomialMod2::Divide(remainder, quotient, *this, b);
	return remainder;
}
