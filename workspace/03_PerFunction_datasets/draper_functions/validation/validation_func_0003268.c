select_item(GooCanvasItem *item) {

  GooCanvasBounds bounds;

  if (moving)
    return;


  g_object_set (red_hands,
		"visibility", GOO_CANVAS_ITEM_INVISIBLE,
		NULL);


  goo_canvas_item_get_bounds(red_hands, &bounds);
  goo_canvas_item_translate(red_hands, -(bounds.x1), -(bounds.y1));


  goo_canvas_item_get_bounds(item, &bounds);
  goo_canvas_item_translate(red_hands, bounds.x1 - 1 , bounds.y1 - 1);

  g_object_set (red_hands,
		"visibility", GOO_CANVAS_ITEM_VISIBLE,
		NULL);

  crane_rope->coords[0] = (bounds.x1 + bounds.x2) / 2;
  crane_rope->coords[1] = CRANE_ROPE_Y;
  crane_rope->coords[2] = (bounds.x1 + bounds.x2) / 2;
  crane_rope->coords[3] = (bounds.y1 + bounds.y2) / 2;

  g_object_set (crane_rope_item,
			 "points", crane_rope,
			 NULL);

  selected_item = item;
}
