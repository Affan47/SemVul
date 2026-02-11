ap_texpr0_node_intlinearize_linear(itv_internal_t* intern,
				   ap_texpr0_node_t* n,
				   itv_linexpr_t* lres )
{
  itv_t i1;
  itv_linexpr_t l1;

  bool exc = n->type!=AP_RTYPE_REAL;
  if (exc) return exc;
  switch (n->op) {
  case AP_TEXPR_NEG:
    exc = itv_intlinearize_ap_texpr0_intlinear(intern,lres,n->exprA);
    itv_linexpr_neg(lres);
    break;

  case AP_TEXPR_CAST:
    break;

  case AP_TEXPR_MOD:
  case AP_TEXPR_SQRT:
    exc = true;
    break;

  case AP_TEXPR_ADD:
  case AP_TEXPR_SUB:
    itv_linexpr_init(&l1,0);


    exc = itv_intlinearize_ap_texpr0_intlinear(intern,&l1,n->exprA);
    exc = itv_intlinearize_ap_texpr0_intlinear(intern,lres,n->exprB) || exc;

    if (n->op==AP_TEXPR_ADD)
      itv_linexpr_add(intern,lres,&l1,lres);
    else
      itv_linexpr_sub(intern,lres,&l1,lres);
    itv_linexpr_clear(&l1);
    break;

  case AP_TEXPR_MUL:
  case AP_TEXPR_DIV:
    itv_init(i1);
    if (ap_texpr0_is_interval_cst(n->exprB)){
      exc = itv_intlinearize_ap_texpr0_intlinear(intern,lres,n->exprA);
      itv_eval_ap_texpr0(intern,i1,n->exprB,NULL);
    }
    else if (n->op == AP_TEXPR_MUL && ap_texpr0_is_interval_cst(n->exprA)){
      exc = itv_intlinearize_ap_texpr0_intlinear(intern,lres,n->exprB);
      itv_eval_ap_texpr0(intern,i1,n->exprA,NULL);
    }
    else {
      exc = true;
      break;
    }
    if (n->op==AP_TEXPR_DIV){
      itv_t i2;
      itv_init(i2);
      itv_set_int(i2,1);
      itv_div(intern,i1,i2,i1);
      itv_clear(i2);
    }
    itv_linexpr_scale(intern,lres,i1);
    itv_clear(i1);
    break;

  default:
    assert(0);
  }
  return exc;
}
