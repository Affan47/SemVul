bq_add_clause_nr(Query *self, BooleanClause *bc)
{
    if (BQ(self)->clause_cnt >= BQ(self)->clause_capa) {
        BQ(self)->clause_capa *= 2;
        REALLOC_N(BQ(self)->clauses, BooleanClause *, BQ(self)->clause_capa);
    }
    if (BQ(self)->clause_cnt > BQ(self)->max_clause_cnt) {
        RAISE(STATE_ERROR, "Two many clauses. The max clause limit is set to "
              "<%d> but your query has <%d> clauses. You can try increasing "
              ":max_clause_count for the BooleanQuery or using a different "
              "type of query.", BQ(self)->clause_cnt, BQ(self)->max_clause_cnt);
    }
    BQ(self)->clauses[BQ(self)->clause_cnt] = bc;
    BQ(self)->clause_cnt++;
    return bc;
}
