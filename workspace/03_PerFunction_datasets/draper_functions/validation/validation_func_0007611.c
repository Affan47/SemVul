gcr_grid_set_boolean (GcrGrid *grid, unsigned row, unsigned column, bool value)
{
	g_return_if_fail (GCR_IS_GRID (grid) && row < grid->rows && column < grid->cols && grid->types[column] == G_TYPE_BOOLEAN);
	grid->row_data[row][column] = value? "t": "f";
	gtk_widget_queue_draw (GTK_WIDGET (grid));
}
