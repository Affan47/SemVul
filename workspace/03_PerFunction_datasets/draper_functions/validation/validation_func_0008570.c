append_hmdf_table_as_leaf(Hmdf_table *item,
                               Block      *bpt,
                               Hmdf_table *parent)
{
    Hmdf_table *tmphmdf = NULL;
    Hmdf_table *phmdf;

    item->block = bpt;
    if (bpt->hmdf == NULL) {
        bpt->hmdf = item;
    }
    else {
        for (tmphmdf = bpt->hmdf
         ; tmphmdf->next != NULL
         ; tmphmdf = tmphmdf->next);

        tmphmdf->next = item;
        item->prev = tmphmdf;
    }

    item->children = bpt->hmdf->children;
    item->parent = parent;
    item->brothers = (item->prev != NULL) ? item->prev->brothers : NULL;
    item->depth = parent->depth + 1;
    if (parent->children == NULL) {
        for (phmdf = parent ; phmdf != NULL ; phmdf=phmdf->next)
            phmdf->children = item;
    }
    else if (item == bpt->hmdf) {
        for (tmphmdf=parent->children
         ; tmphmdf->brothers!=NULL
         ; tmphmdf=tmphmdf->brothers);
        tmphmdf->brothers = item;
    }
}
