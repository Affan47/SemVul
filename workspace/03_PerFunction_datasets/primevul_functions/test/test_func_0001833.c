bool disjointComparisonTypes(Type A, Type B) {
  if (!A.isPrimitive() || !B.isPrimitive())
    return false;


  return Type::intersectTy(A, B).isNoType();
}
