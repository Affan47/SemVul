lyxml_free_withsiblings(struct ly_ctx *ctx, struct lyxml_elem *elem)
{
    FUN_IN;

    struct lyxml_elem *iter, *aux;

    if (!elem) {
        return;
    }


    for(iter = elem->prev; iter->next; iter = aux) {
        aux = iter->prev;
        lyxml_free(ctx, iter);
    }

    LY_TREE_FOR_SAFE(elem, aux, iter) {
        lyxml_free(ctx, iter);
    }
}
