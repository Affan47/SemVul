detect_spy_button()
{
	if( player_spy_count>0 )
	{
		if( button_spy_menu.detect() )
		{
			firm_menu_mode = FIRM_MENU_SPY;
			info.disp();
		}

		if( nation_recno != nation_array.player_recno )
		{
			if( button_bribe.detect() )
			{
				if( player_spy_count > 1 )
				{
					firm_menu_mode = FIRM_MENU_SELECT_BRIBER;
				}
				else
				{
					action_spy_recno = get_player_spy_recno(firm_recno);
					firm_menu_mode   = FIRM_MENU_SET_BRIBE_AMOUNT;
				}

				info.disp();
			}
		}
	}


	if( button_capture.detect() && can_worker_capture(nation_array.player_recno) )
	{

		if( !remote.is_enable() )
		{
			capture_firm(nation_array.player_recno);
		}
		else
		{

			short *shortPtr = (short *)remote.new_send_queue_msg(MSG_FIRM_CAPTURE, 2*sizeof(short) );
			*shortPtr = firm_recno;
			shortPtr[1] = nation_array.player_recno;
		}

	}
}
