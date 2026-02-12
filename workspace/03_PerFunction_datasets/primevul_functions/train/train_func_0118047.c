ExprList_Init(ExprList *l)
{
    l->allocated = EXPRLIST_N_CACHED;
    l->size = 0;


    l->p = l->data;

    ExprList_check_invariants(l);
}
