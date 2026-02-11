DoClampToUint8(HClampToUint8* instr) {
  HValue* value = instr->value();
  Representation input_rep = value->representation();
  LOperand* reg = UseRegister(value);
  if (input_rep.IsDouble()) {
    return DefineAsRegister(new LClampDToUint8(reg,
                                               TempRegister()));
  } else if (input_rep.IsInteger32()) {
    return DefineSameAsFirst(new LClampIToUint8(reg));
  } else {
    ASSERT(input_rep.IsTagged());


    LClampTToUint8* result = new LClampTToUint8(reg,
                                                TempRegister(),
                                                FixedTemp(xmm1));
    return AssignEnvironment(DefineSameAsFirst(result));
  }
}
