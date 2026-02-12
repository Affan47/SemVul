LIR_Address* LIRGenerator::emit_array_address(LIR_Opr array_opr, LIR_Opr index_opr,
                                              BasicType type) {
  int offset_in_bytes = arrayOopDesc::base_offset_in_bytes(type);

  LIR_Address* addr;
  if (index_opr->is_constant()) {
    int elem_size = type2aelembytes(type);
#ifdef _LP64
    jint index = index_opr->as_jint();
    jlong disp = offset_in_bytes + (jlong)(index) * elem_size;
    if (disp > max_jint) {


      index_opr = new_register(T_LONG);
      __ move(LIR_OprFact::longConst(index), index_opr);
      addr = new LIR_Address(array_opr, index_opr, LIR_Address::scale(type), offset_in_bytes, type);
    } else {
      addr = new LIR_Address(array_opr, (intx)disp, type);
    }
#else


    addr = new LIR_Address(array_opr, offset_in_bytes + (intx)(index_opr->as_jint()) * elem_size, type);
#endif
  } else {
#ifdef _LP64
    if (index_opr->type() == T_INT) {
      LIR_Opr tmp = new_register(T_LONG);
      __ convert(Bytecodes::_i2l, index_opr, tmp);
      index_opr = tmp;
    }
#endif
    addr =  new LIR_Address(array_opr,
                            index_opr,
                            LIR_Address::scale(type),
                            offset_in_bytes, type);
  }
  return addr;
}
