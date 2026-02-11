permutePolynomialSet(PolynomialSet const &s, IntegerVector const &v)
{
  PolynomialRing theRing=s.getRing();
  PolynomialSet ret(theRing);
  for(PolynomialSet::const_iterator i=s.begin();i!=s.end();i++)
    {
      ret.push_back(permutePolynomial(*i,v));
    }

  return ret;
}
