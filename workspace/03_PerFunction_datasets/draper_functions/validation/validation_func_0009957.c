gth_grid_view_item_new (GthGridView  *grid_view,
			GthFileData  *file_data,
			GdkPixbuf    *thumbnail,
			gboolean      is_icon,
			char        **attributes_v)
{
	GthGridViewItem *item;

	item = g_new0 (GthGridViewItem, 1);
	item->ref = 1;
	gth_grid_view_item_set_file_data (item, file_data);
	gth_grid_view_item_set_thumbnail (item, thumbnail);
	item->is_icon = is_icon;
	gth_grid_view_item_update_caption (item, attributes_v);

	return item;
}
