REPLACE_ELEM(LINK_ELEMENT *elem1, LINK_ELEMENT *elem2)
{
    elem2->prev = elem1->prev;
    elem2->next = elem1->next;
    if (elem1->prev) {
	elem1->prev->next = elem2;
    }
    if (elem1->next) {
	elem1->next->prev = elem2;
    }
}
