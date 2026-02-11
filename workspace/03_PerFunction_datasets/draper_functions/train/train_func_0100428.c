debug_command_loop (ExecState *state,
			       DATASET *dset,
			       DEBUG_READLINE get_line,
			       DEBUG_OUTPUT put_func,
			       int *errp)
{
    int brk = 0, err = 0;

    state->flags |= DEBUG_EXEC;

    while (!brk) {
#if DDEBUG
	fprintf(stderr, "--- debug_command_loop calling get_line\n");
#endif
	*errp = (*get_line)(state);
	if (*errp) {

	    state->flags &= ~DEBUG_EXEC;
	    return 0;
	}

	err = parse_command_line(state->line, state->cmd,
				 dset, NULL);
	if (err) {
	    if (!strcmp(state->line, "c")) {

		set_debug_cont(state->cmd);
		err = 0;
	    } else if (!strcmp(state->line, "n")) {

		set_debug_next(state->cmd);
		err = 0;
	    }
	}

	if (err || debug_cont(state->cmd) || debug_next(state->cmd)) {
	    brk = 1;
	} else {

	    err = gretl_cmd_exec(state, dset);
	    if (put_func != NULL) {
#if DDEBUG
		fprintf(stderr, "--- debug_command_loop calling put_func\n");
#endif
		(*put_func)(state);
	    }
	}
    }

    if (!debug_next(state->cmd)) {
	state->flags &= ~DEBUG_EXEC;
    }

    return 1 + debug_next(state->cmd);
}
