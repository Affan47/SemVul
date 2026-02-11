set_y_axis_nameCmd()
{
	if (_nword == 5 && !strcmp(_word[3], "label")) {
		if (!strcmp(_word[4], "horizontal"))
			gr_setyaxisstyle(1);
		else if (!strcmp(_word[4], "vertical"))
			gr_setyaxisstyle(0);
		else {
			err("`set y axis name' expecting 'horizontal' or 'vertical', but got `\\", _word[4], "'", "\\");
			demonstrate_command_usage();
			return false;
		}
	} else if (_nword == 5 && !strcmp(_word[3], "name")) {
		if (!strcmp(_word[4], "horizontal"))
			gr_setyaxisstyle(1);
		else if (!strcmp(_word[4], "vertical"))
			gr_setyaxisstyle(0);
		else {
			err("`set y axis name' expecting 'horizontal' or 'vertical', but got `\\", _word[4], "'", "\\");
			demonstrate_command_usage();
			return false;
		}
	}
	return true;
}
