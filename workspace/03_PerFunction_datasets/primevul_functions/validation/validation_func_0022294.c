do_command()
{
    t_iterator *do_iterator;
    int do_start, do_end;
    int end_token;
    char *clause;

    c_token++;
    do_iterator = check_for_iteration();
    if (forever_iteration(do_iterator)) {
	cleanup_iteration(do_iterator);
	int_error(c_token-2, "unbounded iteration not accepted here");
    }

    if (!equals(c_token,"{")) {
	cleanup_iteration(do_iterator);
	int_error(c_token,"expecting {do-clause}");
    }
    end_token = find_clause(&do_start, &do_end);

    clause = new_clause(do_start, do_end);
    begin_clause();

    iteration_depth++;

    if (empty_iteration(do_iterator) && !next_iteration(do_iterator)) {
	strcpy(clause, ";");
    }

    do {
	requested_continue = FALSE;
	do_string(clause);

	if (command_exit_requested != 0)
	    requested_break = TRUE;
	if (requested_break)
	    break;
    } while (next_iteration(do_iterator));
    iteration_depth--;

    free(clause);
    end_clause();
    c_token = end_token;

    do_iterator = cleanup_iteration(do_iterator);
    requested_break = FALSE;
    requested_continue = FALSE;
}
}
