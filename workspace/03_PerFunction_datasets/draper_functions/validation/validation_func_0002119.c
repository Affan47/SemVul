make_new_stm(Quadruple * qr)
{
    Statement * new_stm;
    Quadruple * cur_qr;

    new_stm = alloc_statement();
    new_stm->line_no = 0;
    new_stm->ope = OPE_ASSIGN;
    new_stm->qr_head = qr;
    new_stm->next = NULL;
    new_stm->prev = NULL;
    new_stm->pe_stm = NULL;

    for (cur_qr = qr; cur_qr != NULL; cur_qr = cur_qr->next) {
        cur_qr->stm = new_stm;
    }
    return new_stm;
}
