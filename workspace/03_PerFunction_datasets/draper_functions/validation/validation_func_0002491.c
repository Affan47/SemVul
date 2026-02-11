newBVConstExpr(const std::string& s, int base)
{
  DebugAssert(s.size() > 0,
	      "TheoryBitvector::newBVConstExpr:"
	      "# of subterms must be at least 2");
  DebugAssert(base == 2 || base == 16,
	      "TheoryBitvector::newBVConstExpr: base = "
	      +int2string(base));

  std::string str = s;
  if(16 == base) {
    Rational r(str, 16);
    return newBVConstExpr(r, str.size()*4);
  }
  else {
    BVConstExpr bv(getEM(), str, d_bvConstExprIndex);
    return getEM()->newExpr(&bv);
  }
}
