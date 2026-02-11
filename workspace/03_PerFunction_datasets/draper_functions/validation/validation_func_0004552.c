THX_ck_entersub_establish_cleanup(pTHX_ OP *entersubop, GV *namegv, SV *ckobj)
{
    OP *pushop, *argop, *estop;
    ck_entersub_args_proto(entersubop, namegv, ckobj);
    pushop = cUNOPx(entersubop)->op_first;
    if(!pushop->op_sibling) pushop = cUNOPx(pushop)->op_first;
    argop = pushop->op_sibling;
    pushop->op_sibling = argop->op_sibling;
    argop->op_sibling = NULL;
    op_free(entersubop);
    NewOpSz(0, estop, sizeof(UNOP));
    estop->op_type = OP_RAND;
    estop->op_ppaddr = THX_pp_establish_cleanup;
    cUNOPx(estop)->op_flags = OPf_KIDS;
    cUNOPx(estop)->op_first = argop;
    PL_hints |= HINT_BLOCK_SCOPE;
    return estop;
}
