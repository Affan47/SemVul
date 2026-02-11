ea_cell_table_destroy (EaCellTable *cell_data)
{
	gint index;
	g_return_if_fail (cell_data);

	for (index = 0; index < cell_data->columns; ++index)
		if (cell_data->column_labels[index])
			g_free (cell_data->column_labels[index]);
	g_free (cell_data->column_labels);

	for (index = 0; index < cell_data->rows; ++index)
		if (cell_data->row_labels[index])
			g_free (cell_data->row_labels[index]);
	g_free (cell_data->row_labels);

	for (index = (cell_data->columns * cell_data->rows) -1;
	     index >= 0; --index)
		if (cell_data->cells[index] &&
		    G_IS_OBJECT (cell_data->cells[index]))
			g_object_unref (cell_data->cells[index]);

	g_free (cell_data->cells);
}
