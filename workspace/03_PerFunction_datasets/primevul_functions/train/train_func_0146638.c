init_line_list(line_list *ll, gs_memory_t * mem)
{
    ll->memory = mem;
    ll->active_area = 0;
    ll->next_active = ll->local_active;
    ll->limit = ll->next_active + MAX_LOCAL_ACTIVE;
    ll->close_count = 0;
    ll->y_list = 0;
    ll->y_line = 0;
    ll->h_list0 = ll->h_list1 = 0;

    ll->x_head.prev = NULL;

    ll->x_head.start.x = 0;
    ll->x_head.start.y = 0;
    ll->x_head.end.x = 0;
    ll->x_head.end.y = 0;


    INCR(fill);
}
