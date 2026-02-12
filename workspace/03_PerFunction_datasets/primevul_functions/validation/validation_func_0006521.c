ins_compl_update_sequence_numbers()
{
    int		number = 0;
    compl_T	*match;

    if (compl_dir_forward())
    {


	for (match = compl_curr_match->cp_prev; match != NULL
		&& !is_first_match(match); match = match->cp_prev)
	    if (match->cp_number != -1)
	    {
		number = match->cp_number;
		break;
	    }
	if (match != NULL)


	    for (match = match->cp_next;
		    match != NULL && match->cp_number == -1;
					   match = match->cp_next)
		match->cp_number = ++number;
    }
    else
    {


	for (match = compl_curr_match->cp_next; match != NULL
		&& !is_first_match(match); match = match->cp_next)
	    if (match->cp_number != -1)
	    {
		number = match->cp_number;
		break;
	    }
	if (match != NULL)


	    for (match = match->cp_prev; match
		    && match->cp_number == -1;
					   match = match->cp_prev)
		match->cp_number = ++number;
    }
}
