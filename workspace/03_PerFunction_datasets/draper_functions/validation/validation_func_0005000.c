check_selection()
{
	if(shift_down)
	{
		if(selecting == false)
		{
			selecting = true;
			selection_start = cursor_position;
		}
	}
	else
	{
		selecting = false;
		selection_start = -1;
		selection_end = -1;
	}
}
