_e2_toolbar_mapitem_cb (GtkToolItem *tool, E2_ToolbarRuntime *rt)
{


	GList *item = g_list_find (rt->bar_items_list, tool);

#ifdef FOLDBARS
	if (rt->reversed)
		item = item->prev;
	else
#endif
		item = item->next;

	if (item != NULL)
		rt->menu_starter = GTK_BIN (item->data)->child;
	else
		if (rt->button_rest != NULL)
	{
		gtk_widget_hide (rt->button_rest);
		rt->restbtn_shown = FALSE;
	}
}
