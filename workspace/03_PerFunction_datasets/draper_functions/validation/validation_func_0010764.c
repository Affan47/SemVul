CheckValidSelection(txt_table_t *table)
{
    int rows;
    int new_x, new_y;

    rows = TableRows(table);

    for (new_y = table->selected_y; new_y < rows; ++new_y)
    {
        new_x = FindSelectableColumn(table, new_y, table->selected_x);

        if (new_x >= 0)
        {


            ChangeSelection(table, new_x, new_y);

            break;
        }
    }
}
