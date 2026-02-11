game_run(state_t **_s)
{
	state_t *s = *_s;

	sciprintf(" Calling %s::play()\n", s->game_name);
	_init_stack_base_with_selector(s, s->selector_map.play);


	if (!send_selector(s, s->game_obj, s->game_obj,
			   s->stack_base, 2,
			   s->stack_base) || script_error_flag) {
		objinfo(s, s->game_obj);
		sciprintf("Failed to run the game! Aborting...\n");
		return 1;
	}

	*_s = s = _game_run(s, 0);

	sciprintf(" Game::play() finished.\n");
	return 0;
}
