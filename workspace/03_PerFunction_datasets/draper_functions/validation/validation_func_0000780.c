prq_rewrite(Query *self, IndexReader *ir)
{
    const char *field = PfxQ(self)->field;
    const int field_num = fis_get_field_num(ir->fis, field);
    Query *volatile q = multi_tq_new_conf(field, MTQMaxTerms(self), 0.0);
    q->boost = self->boost;

    if (field_num >= 0) {
        const char *prefix = PfxQ(self)->prefix;
        TermEnum *te = ir->terms_from(ir, field_num, prefix);
        const char *term = te->curr_term;
        size_t prefix_len = strlen(prefix);

        TRY
            do {
                if (strncmp(term, prefix, prefix_len) != 0) {
                    break;
                }
                multi_tq_add_term(q, term);
            } while (te->next(te));
        XFINALLY
            te->close(te);
        XENDTRY
    }

    return q;
}
