maze_create_item(GooCanvasItem *parent)
{
  gchar *message;

  boardRootItem = goo_canvas_group_new (goo_canvas_get_root_item(gcomprisBoard->canvas),
					NULL);

  mazegroup = goo_canvas_group_new(boardRootItem,
				   NULL);

  goo_canvas_item_translate(mazegroup,
			    breedte,
			    hoogte);

  tuxgroup = goo_canvas_group_new(mazegroup,
				   NULL);

  wallgroup = goo_canvas_group_new(boardRootItem,
				   NULL);

  if(modeIsInvisible) {
    message = _("Look at your position, then switch back to invisible mode to continue your moves");
  } else {
    message = _("Look at your position, then switch back to 3D mode to continue your moves");
  }

  warning_item = goo_canvas_text_new (boardRootItem,
				      message,
				      (double) BOARDWIDTH/2,
				      (double) BOARDHEIGHT-BARHEIGHT-25,
				      -1,
				      GTK_ANCHOR_CENTER,
				      "font", gc_skin_font_board_tiny,
				      "fill_color_rgba", gc_skin_color_content,
				      NULL);
  g_object_set (warning_item, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);

  return NULL;
}
