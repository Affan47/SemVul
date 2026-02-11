menu_add_toggle (GtkWidget *menu, menu_entry *me)
{
	GtkWidget *item = NULL;
	char *path = me->path + me->root_offset;

	if (path[0] != 0)
		menu = menu_find_path (menu, path);
	if (menu)
	{
		item = menu_toggle_item (me->label, menu, menu_toggle_cb, me, me->state);
		menu_reorder (GTK_MENU (menu), item, me->pos);
	}
	return item;
}
