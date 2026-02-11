multi_respawn_observer()
{

	Assert(!(Net_player->flags & NETINFO_FLAG_RESPAWNING) && (Net_player->flags & NETINFO_FLAG_LIMBO));


	multi_respawn_as_observer();


	if(!(Net_player->flags & NETINFO_FLAG_AM_MASTER)){
		multi_respawn_send_request(1);
	}


	gameseq_post_event(GS_EVENT_ENTER_GAME);
}
