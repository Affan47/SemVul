void LIRGenerator::do_ArithmeticOp_Long(ArithmeticOp* x) {
  if (x->op() == Bytecodes::_ldiv || x->op() == Bytecodes::_lrem ) {

    LIRItem left(x->x(), this);
    LIRItem right(x->y(), this);


    right.set_destroys_register();

    BasicTypeList signature(2);
    signature.append(T_LONG);
    signature.append(T_LONG);
    CallingConvention* cc = frame_map()->c_calling_convention(&signature);


    CodeEmitInfo* info = state_for(x);

    const LIR_Opr result_reg = result_register_for(x->type());
    left.load_item_force(cc->at(1));
    right.load_item();

    __ move(right.result(), cc->at(0));

    __ cmp(lir_cond_equal, right.result(), LIR_OprFact::longConst(0));
    __ branch(lir_cond_equal, T_LONG, new DivByZeroStub(info));

    address entry = NULL;
    switch (x->op()) {
    case Bytecodes::_lrem:
      entry = CAST_FROM_FN_PTR(address, SharedRuntime::lrem);
      break;
    case Bytecodes::_ldiv:
      entry = CAST_FROM_FN_PTR(address, SharedRuntime::ldiv);
      break;
    case Bytecodes::_lmul:
      entry = CAST_FROM_FN_PTR(address, SharedRuntime::lmul);
      break;
    default:
      ShouldNotReachHere();
    }

    LIR_Opr result = rlock_result(x);
    __ call_runtime_leaf(entry, getThreadTemp(), result_reg, cc->args());
    __ move(result_reg, result);
  } else if (x->op() == Bytecodes::_lmul) {

    LIRItem left(x->x(), this);
    LIRItem right(x->y(), this);


    right.set_destroys_register();

    left.load_item();
    right.load_item();

    LIR_Opr reg = FrameMap::long0_opr;
    arithmetic_op_long(x->op(), reg, left.result(), right.result(), NULL);
    LIR_Opr result = rlock_result(x);
    __ move(reg, result);
  } else {

    LIRItem left(x->x(), this);
    LIRItem right(x->y(), this);

    left.load_item();

    right.load_nonconstant();
    rlock_result(x);
    arithmetic_op_long(x->op(), x->operand(), left.result(), right.result(), NULL);
  }
}
