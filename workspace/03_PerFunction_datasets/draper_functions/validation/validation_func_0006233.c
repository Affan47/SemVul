gen_funcall(CGState *cgs, Exp *e) {
  Value v_params;
  Value *v;
  Value ecx_saved, edx_saved;
  ecx_saved.tag = V_IMM_INT;
  edx_saved.tag = V_IMM_INT;
  v_params.tag = V_IMM_INT;
  gen_saveregs(cgs, &ecx_saved, &edx_saved);
  v_params.u.ival = gen_paramlist(cgs, e->u.funcall.expl, 4);
  gen_unop(cgs, OP_CALL, e->u.funcall.name);
  ALLOC(v, Value);
  v->tag = V_REG;
  v->u.reg = get_reg(cgs);
  if(v->u.reg == REG_EAX) {
    v->tag = V_IND;
    v->u.ind = get_temp(cgs);
  }
  gen_binop(cgs, OP_MOV, REG_EAX, gen_value(v));
  gen_binop(cgs, OP_ADD, gen_value(&v_params), REG_ESP);
  gen_restoreregs(cgs, &ecx_saved, &edx_saved);
  return v;
}
