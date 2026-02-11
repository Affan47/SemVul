process_interpretation(tokens fields) {

	int spine_path_record;
	int i;


	if (new_path) {
		check_new_path(fields);
	}


	for (i = 0; i < fields.number; i += 1) {
		if (strncmp(fields.token[i],"*",1) != 0) {
			print_syntax_error(ERROR6);
		} else if (strcmp(fields.token[i],"**") == 0) {
			print_syntax_error(ERROR7);
		}
	}


	if (!first_interpretation_yet) {
		first_interpretation_yet = TRUE;
		current_no_of_spines = fields.number;
		check_first_interp(fields);
		store_new_interps(fields);


		if (verbose) {
			if (current_no_of_spines > maximum_no_of_spines) {
				maximum_no_of_spines = current_no_of_spines;
			}
			if (current_no_of_spines < minimum_no_of_spines
											|| minimum_no_of_spines == 0) {
				minimum_no_of_spines = current_no_of_spines;
			}
		}


	} else {
		if (fields.number != current_no_of_spines) {
			print_syntax_error(ERROR8);
			current_no_of_spines = fields.number;
		}
		spine_path_record = FALSE;
		for (i = 0; i < fields.number; i += 1) {
			if (strcmp(fields.token[i],"*+") == 0
				   || strcmp(fields.token[i],"*^") == 0
				   || strcmp(fields.token[i],"*-") == 0
				   || strcmp(fields.token[i],"*x") == 0
				   || strcmp(fields.token[i],"*v") == 0) {
				spine_path_record = TRUE;
				break;
			}
		}


		if (spine_path_record) {
			store_indicators(fields);
			process_indicators(fields);


			if (verbose) {
				if (current_no_of_spines > maximum_no_of_spines) {
					maximum_no_of_spines = current_no_of_spines;
				} else if (fields.number < minimum_no_of_spines) {
					minimum_no_of_spines = fields.number;
				}
			}
			if (current_no_of_spines == 0) {
				first_interpretation_yet = FALSE;
			}


		} else {
			store_new_interps(fields);
		}
	}
}
