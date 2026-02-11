restore_cell (BasicCell *bcell, CellBuffer *cb, CellBlock *cursor)
{
    int r, c;

    if (!bcell || !cb || !cursor)
        return;

    if (!cb->changed && !cb->conditionally_changed)
        return;


    for (r = 0; r < cursor->num_rows; r++)
        for (c = 0; c < cursor->num_cols; c++)
        {
            BasicCell *cell;

            cell = gnc_cellblock_get_cell (cursor, r, c);
            if (!cell)
                continue;

            if (cell == bcell)
            {
                gnc_basic_cell_set_value (bcell, cb->value);
                bcell->changed = cb->changed;
                bcell->conditionally_changed = cb->conditionally_changed;
                return;
            }
        }
}
