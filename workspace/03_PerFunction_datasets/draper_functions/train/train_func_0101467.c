setCachedValue(int value) const {
    DebugAssert(!isNull(), "CVC3::Theorem::setCachedValue: we are Null");
    if (isRefl()) exprValue()->d_em->getTM()->setCachedValue((long)d_expr, value);
    else thm()->setCachedValue(value);
  }
