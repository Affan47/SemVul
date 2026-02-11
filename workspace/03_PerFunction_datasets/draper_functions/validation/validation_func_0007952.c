gnc_cellblock_get_cell_by_name(CellBlock *cellblock,
                               const char *cell_name,
                               int *row, int *col)
{
    int r, c, num_rows, num_cols;

    if (cellblock == NULL)
        return NULL;

    if (cell_name == NULL)
        return NULL;

    num_rows = cellblock->num_rows;
    num_cols = cellblock->num_cols;
    for (r = 0; r < num_rows; r++)
        for (c = 0; c < num_cols; c++)
        {
            BasicCell *cell = cellblock->cells->pdata[(r * num_cols) + c];
            if (!cell) continue;
            if (gnc_cell_name_equal(cell->cell_name, cell_name))
            {
                if (row)
                    *row = r;
                if (col)
                    *col = c;
                return cell;
            }
        }

    return NULL;
}
