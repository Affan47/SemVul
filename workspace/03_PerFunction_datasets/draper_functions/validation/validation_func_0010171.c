lj_opt_dse_xstore(jit_State *J)
{
  IRRef xref = fins->op1;
  IRIns *xr = IR(xref);
  IRRef lim = xref;
  IRRef val = fins->op2;
  IRRef1 *refp = &J->chain[IR_XSTORE];
  IRRef ref = *refp;
  if (J->chain[IR_CALLXS] > lim) lim = J->chain[IR_CALLXS];
  if (J->chain[IR_XBAR] > lim) lim = J->chain[IR_XBAR];
  if (J->chain[IR_XSNEW] > lim) lim = J->chain[IR_XSNEW];
  while (ref > lim) {
    IRIns *store = IR(ref);
    switch (aa_xref(J, xr, fins, store)) {
    case ALIAS_NO:
      break;
    case ALIAS_MAY:
      if (store->op2 != val)
	goto doemit;
      break;
    case ALIAS_MUST:
      if (store->op2 == val)
	return DROPFOLD;

      if (ref > J->chain[IR_LOOP]) {
	IRIns *ir;

	for (ir = IR(J->cur.nins-1); ir > store; ir--)
	  if (irt_isguard(ir->t) || ir->o == IR_XLOAD)
	    goto doemit;

	*refp = store->prev;
	store->o = IR_NOP;
	store->t.irt = IRT_NIL;
	store->op1 = store->op2 = 0;
	store->prev = 0;

      }
      goto doemit;
    }
    ref = *(refp = &store->prev);
  }
doemit:
  return EMITFOLD;
}
