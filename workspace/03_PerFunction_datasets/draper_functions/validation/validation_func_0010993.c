tiles_iterator_new(struct tiles *tiles)
{
    struct tiles_iterator *iter = g_new(struct tiles_iterator, 1);

    iter->tiles = tiles;
    iter->first_pass = TRUE;
    iter->current_array_pos = -1;
    iter->remaining_in_pos = 0;

    return iter;
}
