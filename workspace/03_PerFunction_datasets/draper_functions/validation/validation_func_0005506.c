spannq_destroy(Query *self)
{
    SpanNearQuery *snq = SpNQ(self);

    int i;
    for (i = 0; i < snq->c_cnt; i++) {
        Query *clause = snq->clauses[i];
        q_deref(clause);
    }
    free(snq->clauses);

    spanq_destroy_i(self);
}
