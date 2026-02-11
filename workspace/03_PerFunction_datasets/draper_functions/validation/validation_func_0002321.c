Perl_op_free(pTHX_ OP *o)
{
    dVAR;
    OPCODE type;


    assert(!o || !o->op_slabbed || OpSLAB(o)->opslab_refcnt != ~(size_t)0);


    if (!o || o->op_type == OP_FREED)
	return;

    type = o->op_type;
    if (o->op_private & OPpREFCOUNTED) {
	switch (type) {
	case OP_LEAVESUB:
	case OP_LEAVESUBLV:
	case OP_LEAVEEVAL:
	case OP_LEAVE:
	case OP_SCOPE:
	case OP_LEAVEWRITE:
	    {
	    PADOFFSET refcnt;
	    OP_REFCNT_LOCK;
	    refcnt = OpREFCNT_dec(o);
	    OP_REFCNT_UNLOCK;
	    if (refcnt) {


		find_and_forget_pmops(o);
		return;
	    }
	    }
	    break;
	default:
	    break;
	}
    }


    CALL_OPFREEHOOK(o);

    if (o->op_flags & OPf_KIDS) {
        OP *kid, *nextkid;
	for (kid = cUNOPo->op_first; kid; kid = nextkid) {
	    nextkid = kid->op_sibling;
	    op_free(kid);
	}
    }
    if (type == OP_NULL)
	type = (OPCODE)o->op_targ;

    if (o->op_slabbed) {
	Slab_to_rw(OpSLAB(o));
    }


    if (type == OP_NEXTSTATE || type == OP_DBSTATE) {
	cop_free((COP*)o);
    }

    op_clear(o);
    FreeOp(o);
#ifdef DEBUG_LEAKING_SCALARS
    if (PL_op == o)
	PL_op = NULL;
#endif
}
