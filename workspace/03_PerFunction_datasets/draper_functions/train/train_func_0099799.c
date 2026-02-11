make_assign_statement(Statement *spt, Var_table *vpt, int var)
{
    Statement *bb_spt;
    Quadruple *bb_qrpt;
    Operand *assign_opt;

    bb_spt = copy_statement(spt);
    bb_qrpt = bb_spt->qr_head;

    for (; bb_qrpt->next != NULL;) {
	unlink_qr(bb_qrpt->next);
    }

    bb_spt->ope = OPE_ASSIGN;
    bb_spt->dir_pre_head = NULL;
    bb_qrpt->ope = OPE_ASSIGN;
    bb_qrpt->op[0]->kind = KIND_VAR;
    bb_qrpt->op[0]->tbl.v = vpt;
    bb_qrpt->op[0]->entry = vpt->entry;

    assign_opt = get_new_op_const_int(var);
    bb_qrpt->op[1] = assign_opt;

    return bb_spt;
}
