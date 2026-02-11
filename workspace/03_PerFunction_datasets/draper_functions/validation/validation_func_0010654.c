brief_check_for_anim()
{
	int				mx, my, i, iw, ih, x, y;
	brief_stage		*bs;
	brief_icon		*bi = NULL;

	bs = &Briefing->stages[Current_brief_stage];
	mouse_get_pos_unscaled( &mx, &my );


	for (i = 0; i <= BRIEF_BUTTON_FIRST_STAGE; i++) {
		Brief_buttons[gr_screen.res][i].button.get_dimensions(&x, &y, &iw, &ih);

		if (mx >= x && mx <= (x+iw) && my >= y && my <= (y+ih)) {
			return;
		}
 	}


	my -= bscreen.map_y1;
	mx -= bscreen.map_x1;
	if ( my < 0 || mx < 0 || mx > (bscreen.map_x2-bscreen.map_x1+1) || my > (bscreen.map_y2-bscreen.map_y1+1) )
		return;

	for ( i = 0; i < bs->num_icons; i++ ) {
		bi = &bs->icons[i];
		brief_common_get_icon_dimensions(&iw, &ih, bi->type, bi->ship_class);
		if ( mx < bi->x ) continue;
		if ( mx > (bi->x + iw) ) continue;
		if ( my < bi->y ) continue;
		if ( my > (bi->y + ih) ) continue;

		break;
	}

	if ( i == bs->num_icons ) {
		brief_turn_off_closeup_icon();
		return;
	}

	if ( brief_setup_closeup(bi) == 0 ) {
		gamesnd_play_iface(SND_BRIEF_ICON_SELECT);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}
