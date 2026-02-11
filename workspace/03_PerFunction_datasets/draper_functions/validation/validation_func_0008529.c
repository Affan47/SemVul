multi_dcf_kick()
{
	int player_num,idx;


	dc_get_arg(ARG_STRING);

	if(Dc_arg[0] == '\0'){
		dc_printf("Invalid player callsign!\n");
		return ;
	}

	player_num = -1;
	for(idx=0;idx<MAX_PLAYERS;idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && (stricmp(Net_players[idx].m_player->callsign,Dc_arg)==0)){
			player_num = idx;
			break;
		}
	}


	if(player_num == -1){
		dc_printf("Could not find player %s to kick!",Dc_arg);
	}

	else {
		multi_kick_player(player_num);
	}
}
