maximize_fvwm_window(
	FvwmWindow *fw, rectangle *geometry)
{
	SET_MAXIMIZED(fw, 1);
	fw->g.max_defect.width = 0;
	fw->g.max_defect.height = 0;
	constrain_size(
		fw, NULL, &geometry->width, &geometry->height, 0, 0,
		CS_UPDATE_MAX_DEFECT);
	fw->g.max = *geometry;
	if (IS_SHADED(fw))
	{
		get_shaded_geometry(fw, geometry, &fw->g.max);
	}
	frame_setup_window(
		fw, geometry->x, geometry->y, geometry->width,
		geometry->height, True);
	border_draw_decorations(
		fw, PART_ALL, (Scr.Hilite == fw), True, CLEAR_ALL, NULL, NULL);
	update_absolute_geometry(fw);


	fw->g.max_offset.x = fw->g.normal.x - fw->g.max.x;
	fw->g.max_offset.y = fw->g.normal.y - fw->g.max.y;
#if 0
fprintf(stderr,"%d %d %d %d, g.max_offset.x = %d, g.max_offset.y = %d, %d %d %d %d\n", fw->g.max.x, fw->g.max.y, fw->g.max.width, fw->g.max.height, fw->g.max_offset.x, fw->g.max_offset.y, fw->g.normal.x, fw->g.normal.y, fw->g.normal.width, fw->g.normal.height);
#endif

    return;
}
