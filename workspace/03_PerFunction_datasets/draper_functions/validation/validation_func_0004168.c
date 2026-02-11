multi_tq_extract_terms(Query *self, HashSet *terms)
{
    int i;
    char *field = MTQ(self)->field;
    PriorityQueue *boosted_terms = MTQ(self)->boosted_terms;
    for (i = boosted_terms->size; i > 0; i--) {
        BoostedTerm *bt = (BoostedTerm *)boosted_terms->heap[i];
        hs_add(terms, term_new(field, bt->term));
    }
}
