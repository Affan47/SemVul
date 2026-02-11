item_event (GooCanvasItem  *item,
	    GooCanvasItem  *target,
	    GdkEventButton *event,
	    MachItem *machItem)
{
  double item_x, item_y;
  GooCanvasBounds bounds;
  double width;
  item_x = event->x;
  item_y = event->y;

  goo_canvas_convert_from_item_space(goo_canvas_item_get_canvas(item),
				     item, &item_x, &item_y);

  goo_canvas_item_get_bounds (item, &bounds);

  if(board_paused)
    return FALSE;

  gc_sound_play_ogg ("sounds/scroll.wav", NULL);
  width = bounds.x2 - bounds.x1;

  machItem->times = 0;
  machItem->yposo = machItem->ypos;
  machItem->xposo = machItem->xpos;

  machItem->vyo = ((item_y-bounds.y1)<width/2?(width/2-(item_y-bounds.y1))*20:-1*(width/2-(bounds.y2-item_y))*20);
  machItem->vxo = ((item_x-bounds.x1)<width/2?(width/2-(item_x-bounds.x1))*20:-1*(width/2-(bounds.x2-item_x))*20);

  return FALSE;
}
