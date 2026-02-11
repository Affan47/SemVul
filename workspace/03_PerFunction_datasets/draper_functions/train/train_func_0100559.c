q_create(size_t size)
{
    Query *self = (Query *)ecalloc(size);
#ifdef DEBUG
    if (size < sizeof(Query)) {
        RAISE(FERRET_ERROR, "Size of a query <%d> should never be smaller than the "
              "size of a Query struct <%d>", (int)size, (int)sizeof(Query));
    }
#endif
    self->boost             = 1.0;
    self->rewrite           = &q_rewrite;
    self->get_similarity    = &q_get_similarity_i;
    self->extract_terms     = &q_extract_terms;
    self->get_matchv_i      = &q_get_matchv_i;
    self->weight            = NULL;
    self->ref_cnt           = 1;
    return self;
}
