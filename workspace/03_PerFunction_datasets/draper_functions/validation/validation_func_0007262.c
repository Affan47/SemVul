CMD_GotoDeskAndPage(F_CMD_ARGS)
{
	int val[3];
	Bool is_new_desk;

	if (MatchToken(action, "prev"))
	{
		val[0] = prev_desk_and_page_desk;
		val[1] = prev_desk_and_page_page_x;
		val[2] = prev_desk_and_page_page_y;
	}
	else if (GetIntegerArguments(action, NULL, val, 3) == 3)
	{
		val[1] *= Scr.MyDisplayWidth;
		val[2] *= Scr.MyDisplayHeight;
	}
	else
	{
		return;
	}

	is_new_desk = (Scr.CurrentDesk != val[0]);
	if (is_new_desk)
	{
		UnmapDesk(Scr.CurrentDesk, True);
	}
	prev_desk_and_page_page_x = Scr.Vx;
	prev_desk_and_page_page_y = Scr.Vy;
	MoveViewport(val[1], val[2], True);
	if (is_new_desk)
	{
		prev_desk = Scr.CurrentDesk;
		prev_desk_and_page_desk = Scr.CurrentDesk;
		Scr.CurrentDesk = val[0];
		MapDesk(val[0], True);
		focus_grab_buttons_all();
		BroadcastPacket(M_NEW_DESK, 1, (long)Scr.CurrentDesk);


		BroadcastRestackAllWindows();
	}
	else
	{
		BroadcastPacket(M_NEW_DESK, 1, (long)Scr.CurrentDesk);
	}
	EWMH_SetCurrentDesktop();
	GNOME_SetCurrentDesk();
	GNOME_SetDeskCount();

	return;
}
