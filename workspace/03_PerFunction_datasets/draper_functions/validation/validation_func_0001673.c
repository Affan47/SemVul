dupe_menu_popup_main(DupeWindow *dw, DupeItem *di)
{
	GtkWidget *menu;
	GtkWidget *item;
	gint on_row;
	GList *editmenu_fd_list;

	on_row = (di != NULL);

	menu = popup_menu_short_lived();

	menu_item_add_sensitive(menu, _("_View"), on_row,
				G_CALLBACK(dupe_menu_view_cb), dw);
	menu_item_add_stock_sensitive(menu, _("View in _new window"), GTK_STOCK_NEW, on_row,
				G_CALLBACK(dupe_menu_viewnew_cb), dw);
	menu_item_add_divider(menu);
	menu_item_add_sensitive(menu, _("Select all"), (dw->dupes != NULL),
				G_CALLBACK(dupe_menu_select_all_cb), dw);
	menu_item_add_sensitive(menu, _("Select none"), (dw->dupes != NULL),
				G_CALLBACK(dupe_menu_select_none_cb), dw);
	menu_item_add_sensitive(menu, _("Select group _1 duplicates"), (dw->dupes != NULL),
				G_CALLBACK(dupe_menu_select_dupes_set1_cb), dw);
	menu_item_add_sensitive(menu, _("Select group _2 duplicates"), (dw->dupes != NULL),
				G_CALLBACK(dupe_menu_select_dupes_set2_cb), dw);
	menu_item_add_divider(menu);

	editmenu_fd_list = dupe_window_get_fd_list(dw);
	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(dupe_menu_popup_destroy_cb), editmenu_fd_list);
	submenu_add_edit(menu, &item, G_CALLBACK(dupe_menu_edit_cb), dw, editmenu_fd_list);
	if (!on_row) gtk_widget_set_sensitive(item, FALSE);
	menu_item_add_stock_sensitive(menu, _("Add to new collection"), GTK_STOCK_INDEX, on_row,
				G_CALLBACK(dupe_menu_collection_cb), dw);
	menu_item_add_stock_sensitive(menu, _("Print..."), GTK_STOCK_PRINT, on_row,
				G_CALLBACK(dupe_menu_print_cb), dw);
	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("_Copy..."), GTK_STOCK_COPY, on_row,
				G_CALLBACK(dupe_menu_copy_cb), dw);
	menu_item_add_sensitive(menu, _("_Move..."), on_row,
				G_CALLBACK(dupe_menu_move_cb), dw);
	menu_item_add_sensitive(menu, _("_Rename..."), on_row,
				G_CALLBACK(dupe_menu_rename_cb), dw);
	menu_item_add_stock_sensitive(menu, _("_Delete..."), GTK_STOCK_DELETE, on_row,
				G_CALLBACK(dupe_menu_delete_cb), dw);
	menu_item_add_sensitive(menu, _("_Copy path"), on_row,
				G_CALLBACK(dupe_menu_copy_path_cb), dw);
	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("Rem_ove"), GTK_STOCK_REMOVE, on_row,
				G_CALLBACK(dupe_menu_remove_cb), dw);
	menu_item_add_stock_sensitive(menu, _("C_lear"), GTK_STOCK_CLEAR, (dw->list != NULL),
				G_CALLBACK(dupe_menu_clear_cb), dw);
	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("Close _window"), GTK_STOCK_CLOSE,
			    G_CALLBACK(dupe_menu_close_cb), dw);

	return menu;
}
