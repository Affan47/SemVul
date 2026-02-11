mp_loop(midi_player_t *mp)
{
	int i;
	for(i = 0; i < 16; i++)
		if(mp->track[i].enabled)
			mp->track[i].c = mp->track[i].loop_start;
	mp_print_time(mp, mp->c.time);
	midiprintf(D2LOG, ": mp_loop\n");
	mp->c = mp->loop_start;
}
