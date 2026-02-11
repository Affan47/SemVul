_mesa_symbol_table_iterator_next(struct _mesa_symbol_table_iterator *iter)
{
    struct symbol_header *hdr;

    if (iter->curr == NULL) {
        return 0;
    }

    hdr = iter->curr->hdr;
    iter->curr = iter->curr->next_with_same_name;

    while (iter->curr != NULL) {
        assert(iter->curr->hdr == hdr);

        if ((iter->name_space == -1)
            || (iter->curr->name_space == iter->name_space)) {
            return 1;
        }

        iter->curr = iter->curr->next_with_same_name;
    }

    return 0;
}
