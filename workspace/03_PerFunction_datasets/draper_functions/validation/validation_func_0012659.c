multi_pinfo_popup_button_pressed(int n)
{
	net_player *swap;

	switch(n){
	case MPI_EXIT:
		Multi_pinfo_popup_done = 1;
		break;

	case MPI_MEDALS:
		gamesnd_play_iface(SND_USER_SELECT);
		multi_pinfo_do_medals();
		break;

	case MPI_SCROLL_STATS_UP:
		swap = multi_pinfo_get_prev_player(Multi_pinfo_popup_player);
		if(swap != NULL){
			gamesnd_play_iface(SND_USER_SELECT);
			multi_pinfo_reset_player(swap);
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;

	case MPI_SCROLL_STATS_DOWN:
		swap = multi_pinfo_get_next_player(Multi_pinfo_popup_player);
		if(swap != NULL){
			gamesnd_play_iface(SND_USER_SELECT);
			multi_pinfo_reset_player(swap);
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;

	default :
		gamesnd_play_iface(SND_GENERAL_FAIL);
		break;
	}
}
