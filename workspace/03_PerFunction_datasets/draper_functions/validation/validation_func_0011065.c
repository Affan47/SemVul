esma_change_cursor (ESelectionModel *selection,
                    gint row,
                    gint col)
{
	ESelectionModelArray *esma;

	g_return_if_fail (selection != NULL);
	g_return_if_fail (E_IS_SELECTION_MODEL (selection));

	esma = E_SELECTION_MODEL_ARRAY (selection);

	esma->cursor_row = row;
	esma->cursor_col = col;
	esma->cursor_row_sorted = es_row_model_to_sorted (esma, esma->cursor_row);
}
