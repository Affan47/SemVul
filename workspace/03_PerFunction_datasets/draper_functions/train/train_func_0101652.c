ectr_subcell_weak_ref (GalA11yECellTree *a11y,
                       GalA11yECell *subcell_a11y)
{
	ECellView *subcell_view = subcell_a11y ? subcell_a11y->cell_view : NULL;
	if (subcell_a11y && subcell_view && subcell_view->kill_view_cb_data)
	    subcell_view->kill_view_cb_data = g_list_remove (subcell_view->kill_view_cb_data, subcell_a11y);

	g_signal_handler_disconnect (
		GAL_A11Y_E_CELL (a11y)->item->table_model,
		a11y->model_row_changed_id);
	g_object_unref (a11y);
}
