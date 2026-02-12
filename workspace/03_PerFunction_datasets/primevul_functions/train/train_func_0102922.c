bool LIRGenerator::can_store_as_constant(Value v, BasicType type) const {
  if (type == T_SHORT || type == T_CHAR) {

    return false;
  }
  Constant* c = v->as_Constant();
  if (c && c->state_before() == NULL) {


    return true;
  }
  return false;
}
