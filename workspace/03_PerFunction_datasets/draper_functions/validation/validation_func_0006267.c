CMD_HideGeometryWindow(F_CMD_ARGS)
{
	char *token = PeekToken(action, NULL);

	Scr.gs.do_hide_position_window = 0;
	Scr.gs.do_hide_resize_window = 0;
	switch(GetTokenIndex(token, hide_options, 0, NULL))
	{
	case 0:
		break;
	case 1:
		Scr.gs.do_hide_position_window = 1;
		break;
	case 2:
		Scr.gs.do_hide_resize_window = 1;
		break;
	default:
		Scr.gs.do_hide_position_window = 1;
		Scr.gs.do_hide_resize_window = 1;
		break;
	}
	return;
}
