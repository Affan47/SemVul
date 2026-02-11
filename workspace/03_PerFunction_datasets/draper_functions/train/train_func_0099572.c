spif_linked_list_reverse(spif_linked_list_t self)
{
    spif_linked_list_item_t current, tmp, previous;

    ASSERT_RVAL(!SPIF_LIST_ISNULL(self), FALSE);
    for (previous = SPIF_NULL_TYPE(linked_list_item), current = self->head; current; previous = tmp) {
        tmp = current;
        current = current->next;
        tmp->next = previous;
    }
    self->head = tmp;
    return TRUE;
}
