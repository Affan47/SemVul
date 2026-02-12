LIR_Opr LIRGenerator::atomic_add(BasicType type, LIR_Opr addr, LIRItem& value) {
  LIR_Opr result = new_register(type);
  value.load_item();

  __ move(value.result(), result);
  assert(type == T_INT LP64_ONLY( || type == T_LONG ), "unexpected type");
  __ xadd(addr, result, result, LIR_OprFact::illegalOpr);
  return result;
}
