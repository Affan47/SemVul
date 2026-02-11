gtk_cmclist_drag_leave (GtkWidget      *widget,
		      GdkDragContext *context,
		      guint           time)
{
  GtkCMCList *clist;
  GtkCMCListDestInfo *dest_info;

  cm_return_if_fail (GTK_IS_CMCLIST (widget));
  cm_return_if_fail (context != NULL);

  clist = GTK_CMCLIST (widget);

  dest_info = g_dataset_get_data (context, "gtk-clist-drag-dest");

  if (dest_info)
    {
      if (dest_info->cell.row >= 0 &&
	  GTK_CMCLIST_REORDERABLE(clist) &&
	  gtk_drag_get_source_widget (context) == widget)
	{
	  GdkAtom atom = gdk_atom_intern_static_string ("gtk-clist-drag-reorder");
	  GdkAtom found = gtk_drag_dest_find_target(widget, context, NULL);

	      if (atom == found)
		{
		  clist->drag_highlight_row = -1;
		}
	}
      g_dataset_remove_data (context, "gtk-clist-drag-dest");
    }
}
