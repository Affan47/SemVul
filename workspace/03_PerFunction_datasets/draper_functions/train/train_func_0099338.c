glade_gtk_tool_item_post_create (GladeWidgetAdaptor *adaptor,
                                 GObject            *object,
				 GladeCreateReason   reason)
{
  if (GTK_IS_SEPARATOR_TOOL_ITEM (object))
    return;

  if (reason == GLADE_CREATE_USER &&
      gtk_bin_get_child (GTK_BIN (object)) == NULL)
    gtk_container_add (GTK_CONTAINER (object), glade_placeholder_new ());
}
