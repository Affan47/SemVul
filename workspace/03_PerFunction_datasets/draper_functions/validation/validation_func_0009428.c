fm_nav_history_go_to(FmNavHistory* nh, guint n, gint old_scroll_pos)
{
    GList *link;

    g_return_val_if_fail(nh != NULL && FM_IS_NAV_HISTORY(nh), NULL);
    if(nh->cur)
        ((FmNavHistoryItem*)nh->cur->data)->scroll_pos = old_scroll_pos;
    if(n == nh->n_cur)
        return ((FmNavHistoryItem*)nh->cur->data)->path;
    link = g_queue_peek_nth_link(&nh->items, n);
    if(link == NULL)
        return NULL;
    nh->n_cur = n;
    nh->cur = link;
    return ((FmNavHistoryItem*)link->data)->path;
}
