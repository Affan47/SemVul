remove_jump_pe_stm(Pe_statement *pestm)
{
    Statement *s;
    Statement *next;

    s = pestm->stm_head;
    while (s != NULL) {
        next = s->next;
        remove_jump_stm(s);
        if (s->qr_head == NULL) {
            unlink_statement(s);
            free_statement(s);
        }
        s = next;
    }
}
