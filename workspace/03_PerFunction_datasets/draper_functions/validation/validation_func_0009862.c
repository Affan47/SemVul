hud_squadmsg_end()
{


	if ( message_is_playing() == FALSE )
		snd_play( &Snds[SND_SQUADMSGING_OFF] );
}
