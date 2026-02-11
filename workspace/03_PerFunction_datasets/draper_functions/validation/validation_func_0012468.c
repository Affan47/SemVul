multi_endgame_process()
{
	if ( Multi_endgame_processing )
		return;

	Multi_endgame_processing = 1;


	multi_endgame_check_for_warpout();


	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

		if(!Multi_endgame_server_waiting){
			Multi_endgame_processing = 0;
			return;
		}


		if(popup_active()){
			Multi_endgame_processing = 0;
			return;
		}


		if(!multi_endgame_server_ok_to_leave()){
			if(Game_mode & GM_STANDALONE_SERVER){
				while(!multi_endgame_server_ok_to_leave()){

					game_set_frametime(-1);
					game_do_state_common(gameseq_get_state());
				}
			} else {
				popup_till_condition( multi_endgame_server_ok_to_leave , XSTR("&Cancel",645), XSTR("Waiting for clients to disconnect",646));
			}
		}


		multi_endgame_cleanup();
	} else {

		if(!Multi_endgame_client_waiting){
			Multi_endgame_processing = 0;
			return;
		}


		if(popup_active()){
			Multi_endgame_processing = 0;
			return;
		}


		multi_endgame_cleanup();
	}

	Multi_endgame_processing = 0;
}
