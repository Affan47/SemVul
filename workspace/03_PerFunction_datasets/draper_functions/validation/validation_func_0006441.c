operator==(const ExprValue& ev2) const {
  DebugAssert(getMMIndex() == EXPR_VALUE,
	      "ExprValue::operator==() called from a subclass");
  if(getMMIndex() != ev2.getMMIndex())
    return false;

  return (d_kind == ev2.d_kind);
}
