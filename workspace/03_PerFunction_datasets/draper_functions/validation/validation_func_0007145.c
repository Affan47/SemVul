do_birth_reset(bool use_quickstart, birther *quickstart_prev)
{
	player_wipe();


	if (use_quickstart && quickstart_prev)
		load_roller_data(quickstart_prev, NULL);

	generate_player();


	get_bonuses();
}
