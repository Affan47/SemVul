il_read_line(static_text, dest, default_string, history)
    char *static_text;
    char **dest;
    char *default_string;
    xstack_t *history;
{
    tty_key_t *ks;
    char *history_text;
    command_t *command;
    int key = 0, repeat_count, offset = 0;


    il_reset_line();

    if (static_text)
	il_set_static_text(static_text);

    if (default_string)
	il_insert_text(default_string);

    if (history && default_string)
    {
	il_history_add_entry(history, default_string);
	offset = 1;
    }

    il_update();
    il_update_point();
    tty_update();

    while (1)
    {
	while ((ks = tty_get_key(&repeat_count)) == NULL)
	{
	    tty_beep();
	    status_update();
	    il_update_point();
	}

	key = ks->key_seq[0];
	command = (command_t *)ks->aux_data;

	if (command && command->builtin)
	    key = - 1 - (command->name - builtin[0]) / MAX_BUILTIN_NAME;

	switch (key)
	{
	    case BUILTIN_previous_line:
	    case BUILTIN_previous_history_element:
		if (history == NULL)
		    break;

		history_text = il_history_view_entry(history, ++offset);

		if (history_text == NULL)
		{
		    offset--;
		    tty_beep();
		}
		else
		{
		    il_kill_line(IL_DONT_STORE);
		    il_insert_text(history_text);
		    il_update();
		    il_update_point();
		}
		break;

	    case BUILTIN_next_line:
	    case BUILTIN_next_history_element:
		if (history == NULL)
		    break;

		if (offset == 0)
		{
		    il_kill_line(IL_DONT_STORE);
		    il_update();
		    il_update_point();
		    break;
		}

		il_kill_line(IL_DONT_STORE);

		offset--;

		if (offset > 0)
		{
		    history_text = il_history_view_entry(history, offset);
		    il_insert_text(history_text);
		}

		il_update();
		il_update_point();
		break;

	    case BUILTIN_refresh:
		refresh(0);
		break;

	    case BUILTIN_action:
		il_get_contents(dest);

	    case key_INTERRUPT:
		goto done;

	    default:
		while (repeat_count--)
		    if (il_dispatch_commands(key, IL_MOVE | IL_EDIT) == 0)
			tty_beep();

		il_update();
		break;
	}

	status_update();
	il_update_point();
	tty_update();
    }

  done:
    if (key == BUILTIN_action)
    {
	if (history)
	    il_history_add_entry(history, *dest);
	return *dest;
    }
    else
	return NULL;
}
