FScreenSetState(Bool do_enable)
{
	is_xinerama_enabled = do_enable;
	if (do_enable && total_screens > 0)
	{
		num_screens = total_screens;
		first_to_check = 1;
		last_to_check  = total_screens;
	}
	else
	{
		num_screens = 0;
		first_to_check = 0;
		last_to_check = 0;
	}
	FScreenUpdateEmulationMapState();
}
