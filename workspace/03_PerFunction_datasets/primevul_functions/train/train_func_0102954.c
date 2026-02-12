void LIRGenerator::do_ArithmeticOp_Int(ArithmeticOp* x) {
  if (x->op() == Bytecodes::_idiv || x->op() == Bytecodes::_irem) {


    LIRItem right(x->y(), this);
    LIRItem left(x->x() , this);


    CodeEmitInfo* info = state_for(x);

    left.load_item_force(divInOpr());

    right.load_item();

    LIR_Opr result = rlock_result(x);
    LIR_Opr result_reg;
    if (x->op() == Bytecodes::_idiv) {
      result_reg = divOutOpr();
    } else {
      result_reg = remOutOpr();
    }

    if (!ImplicitDiv0Checks) {
      __ cmp(lir_cond_equal, right.result(), LIR_OprFact::intConst(0));
      __ branch(lir_cond_equal, T_INT, new DivByZeroStub(info));

      info = NULL;
    }
    LIR_Opr tmp = FrameMap::rdx_opr;
    if (x->op() == Bytecodes::_irem) {
      __ irem(left.result(), right.result(), result_reg, tmp, info);
    } else if (x->op() == Bytecodes::_idiv) {
      __ idiv(left.result(), right.result(), result_reg, tmp, info);
    } else {
      ShouldNotReachHere();
    }

    __ move(result_reg, result);
  } else {

    LIRItem left(x->x(),  this);
    LIRItem right(x->y(), this);
    LIRItem* left_arg = &left;
    LIRItem* right_arg = &right;
    if (x->is_commutative() && left.is_stack() && right.is_register()) {

      left_arg = &right;
      right_arg = &left;
    }

    left_arg->load_item();


    if (x->op() == Bytecodes::_imul ) {

      bool use_constant = false;
      bool use_tmp = false;
      if (right_arg->is_constant()) {
        jint iconst = right_arg->get_jint_constant();
        if (iconst > 0 && iconst < max_jint) {
          if (is_power_of_2(iconst)) {
            use_constant = true;
          } else if (is_power_of_2(iconst - 1) || is_power_of_2(iconst + 1)) {
            use_constant = true;
            use_tmp = true;
          }
        }
      }
      if (use_constant) {
        right_arg->dont_load_item();
      } else {
        right_arg->load_item();
      }
      LIR_Opr tmp = LIR_OprFact::illegalOpr;
      if (use_tmp) {
        tmp = new_register(T_INT);
      }
      rlock_result(x);

      arithmetic_op_int(x->op(), x->operand(), left_arg->result(), right_arg->result(), tmp);
    } else {
      right_arg->dont_load_item();
      rlock_result(x);
      LIR_Opr tmp = LIR_OprFact::illegalOpr;
      arithmetic_op_int(x->op(), x->operand(), left_arg->result(), right_arg->result(), tmp);
    }
  }
}
