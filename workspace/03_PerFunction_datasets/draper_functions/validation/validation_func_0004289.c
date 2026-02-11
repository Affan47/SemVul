search_free_by_time(List *bus_state, real target_time)
{
    List *li;
    Data_trans_group *tmp, *next;

    for (li = bus_state; li->next != NULL; li = li->next) {
        tmp = li->data;
        next = li->next->data;
        if (tmp->trans_end_time <= target_time
            && next->trans_start_time > target_time)
            return li;
    }
    return NULL;
}
