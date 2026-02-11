gtk_cmclist_get_text (GtkCMCList  *clist,
		    gint       row,
		    gint       column,
		    gchar    **text)
{
  GtkCMCListRow *clist_row;

  cm_return_val_if_fail (GTK_IS_CMCLIST (clist), 0);

  if (row < 0 || row >= clist->rows)
    return 0;
  if (column < 0 || column >= clist->columns)
    return 0;

  clist_row = ROW_ELEMENT (clist, row)->data;

  if (clist_row->cell[column].type != GTK_CMCELL_TEXT)
    return 0;

  if (text)
    *text = GTK_CMCELL_TEXT (clist_row->cell[column])->text;

  return 1;
}
