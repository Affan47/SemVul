should_disp()
{
	if( config.help_mode == NO_HELP )
		return 0;

	if( VBrowse::press_record )
		return 0;

	if( last_mouse_x==mouse.cur_x && last_mouse_y==mouse.cur_y &&
		 !mouse.left_press && !mouse.right_press && !mouse.any_click(2) )
	{
		if( misc.get_time() >= mouse_still_time + HELP_INACTIVE_TIME * 1000 )
		{
			return 1;
		}
	}
	else
	{
		last_mouse_x = mouse.cur_x;
		last_mouse_y = mouse.cur_y;
		mouse_still_time = misc.get_time();
	}

	return 0;
}
