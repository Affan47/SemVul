ExprList_Dealloc(ExprList *l)
{
    ExprList_check_invariants(l);


    if (!l->p || l->p == l->data) {

    } else {

        PyMem_RawFree(l->p);
    }
    l->p = NULL;
    l->size = -1;
}
