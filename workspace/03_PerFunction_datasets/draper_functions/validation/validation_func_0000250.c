conn_insert(conn head, conn c)
{
    if (conn_list_any_p(c)) return;

    c->prev = head->prev;
    c->next = head;
    head->prev->next = c;
    head->prev = c;
}
