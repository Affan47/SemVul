planegame_move_items (GtkWidget *widget, gpointer data)
{
  int i;


  for(i = 0;
      i < goo_canvas_item_get_n_children(clouds_rootitem);
      i++)
    planegame_cloud_colision(goo_canvas_item_get_child(clouds_rootitem,
							 i));


  planegame_move_plane(planeitem);
  planemove_id = g_timeout_add (speed,
				(GSourceFunc) planegame_move_items, NULL);

  return(FALSE);
}
