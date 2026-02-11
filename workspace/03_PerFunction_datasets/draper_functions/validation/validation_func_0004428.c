put_crosshair()
{
	if(_state != normal)
		return;
	if(!crosshair)
	{
		crosshair = gengine->get_obj(LAYER_OVERLAY);
		if(crosshair)
			cs_obj_show(crosshair);
	}
	if(crosshair)
	{
		cs_obj_image(crosshair, B_CROSSHAIR, 0);
		crosshair->point.v.x = PIXEL2CS(mouse_x - 8 - MARGIN);
		crosshair->point.v.y = PIXEL2CS(mouse_y - MARGIN);
	}
}
