operator/(const Monomial &b)const
{
  return Term(c,Monomial(theRing,m.exponent-b.exponent));
}
