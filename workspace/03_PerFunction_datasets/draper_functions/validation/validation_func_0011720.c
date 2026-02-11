multi_tq_get_matchv_i(Query *self, MatchVector *mv,
                                          TermVector *tv)
{
    if (tv->field == MTQ(self)->field) {
        int i;
        PriorityQueue *boosted_terms = MTQ(self)->boosted_terms;
        for (i = boosted_terms->size; i > 0; i--) {
            int j;
            BoostedTerm *bt = (BoostedTerm *)boosted_terms->heap[i];
            TVTerm *tv_term = tv_get_tv_term(tv, bt->term);
            if (tv_term) {
                for (j = 0; j < tv_term->freq; j++) {
                    int pos = tv_term->positions[j];
                    matchv_add(mv, pos, pos);
                }
            }
        }
    }
    return mv;
}
