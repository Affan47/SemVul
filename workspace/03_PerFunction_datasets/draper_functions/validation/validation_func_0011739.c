multi_debrief_server_process()
{
	int idx;
	int player_status,other_status;

	Multi_debrief_server_framecount++;


	if((Multi_debrief_time >= Multi_debrief_resend_time) && !multi_netplayer_state_check3(NETPLAYER_STATE_DEBRIEF, NETPLAYER_STATE_DEBRIEF_ACCEPT, NETPLAYER_STATE_DEBRIEF_REPLAY, 1)){

		for(idx=0; idx<MAX_PLAYERS; idx++){
			if( MULTI_CONNECTED(Net_players[idx]) && (Net_player != &Net_players[idx]) &&
				( ( Net_players[idx].state != NETPLAYER_STATE_DEBRIEF ) &&
				  ( Net_players[idx].state != NETPLAYER_STATE_DEBRIEF_ACCEPT ) &&
				  ( Net_players[idx].state != NETPLAYER_STATE_DEBRIEF_REPLAY ) ) ){
				send_endgame_packet(&Net_players[idx]);
			}
		}


		Multi_debrief_resend_time += 7.0f;
	}


	other_status = 1;


	for(idx=0;idx<MAX_PLAYERS;idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_HOST(Net_players[idx])){
			if(Net_players[idx].state != NETPLAYER_STATE_DEBRIEF_ACCEPT){
				other_status = 0;
				break;
			}
		}
	}


	if(multi_netplayer_state_check3(NETPLAYER_STATE_DEBRIEF, NETPLAYER_STATE_DEBRIEF_ACCEPT, NETPLAYER_STATE_DEBRIEF_REPLAY) && (Netgame.type_flags & NG_TYPE_TEAM) && !Multi_debrief_reported_tvt && (Multi_debrief_server_framecount > 4)){
		multi_team_report();
		Multi_debrief_reported_tvt = 1;
	}


	if(other_status){

		if(Netgame.host->state == NETPLAYER_STATE_DEBRIEF_ACCEPT){
			player_status = 1;
		}

		else if(Netgame.host->state == NETPLAYER_STATE_DEBRIEF_REPLAY){
			player_status = 2;
		}

		else {
			player_status = 0;
		}
	}

	else {
		player_status = 0;
	}


	if(Netgame.campaign_mode == MP_CAMPAIGN){
		multi_campaign_do_debrief(player_status);
	}

	else {
		if(player_status == 1){
			multi_flush_mission_stuff();


			Netgame.game_state = NETGAME_STATE_FORMING;
			send_netgame_update_packet();


			if(Game_mode & GM_STANDALONE_SERVER){
				gameseq_post_event(GS_EVENT_STANDALONE_MAIN);
			} else {
				gameseq_post_event(GS_EVENT_MULTI_HOST_SETUP);
			}

			multi_reset_timestamps();
		} else if(player_status == 2){
			multi_flush_mission_stuff();


			Netgame.game_state = NETGAME_STATE_MISSION_SYNC;
			send_netgame_update_packet();


			Multi_sync_mode = MULTI_SYNC_PRE_BRIEFING;
			gameseq_post_event(GS_EVENT_MULTI_MISSION_SYNC);

			multi_reset_timestamps();
		}
	}
}
