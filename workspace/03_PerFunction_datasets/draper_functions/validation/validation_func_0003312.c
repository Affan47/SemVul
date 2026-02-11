e_cell_free_state (ECellView *ecell_view,
                   gint model_col,
                   gint view_col,
                   gint row,
                   gpointer save_state)
{
	ECellClass *class;

	class = E_CELL_GET_CLASS (ecell_view->ecell);

	if (class->free_state != NULL)
		class->free_state (
			ecell_view, model_col, view_col, row, save_state);
}
