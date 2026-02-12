LiteralNumber *hermes::evalToInt32(IRBuilder &builder, Literal *operand) {

  LiteralNumber *lit = evalToNumber(builder, operand);
  if (!lit) {
    return nullptr;
  }
  double val = lit->getValue();
  return builder.getLiteralNumber(truncateToInt32(val));
}
