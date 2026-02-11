eel_canvas_item_invoke_point (EelCanvasItem *item, double x, double y, int cx, int cy, EelCanvasItem **actual_item)
{


	if (EEL_CANVAS_ITEM_GET_CLASS (item)->point)
		return EEL_CANVAS_ITEM_GET_CLASS (item)->point (item, x, y, cx, cy, actual_item);

	return 1e18;
}
