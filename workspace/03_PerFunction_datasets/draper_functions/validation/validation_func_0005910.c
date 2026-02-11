update_relative_geometry(FvwmWindow *fw)
{
	get_relative_geometry(
		&fw->g.frame,
		(IS_MAXIMIZED(fw)) ? &fw->g.max : &fw->g.normal);
	if (IS_SHADED(fw))
	{
		get_shaded_geometry(
			fw, &fw->g.frame, &fw->g.frame);
	}

	return;
}
