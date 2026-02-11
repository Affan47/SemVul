TRANS_tree()
{
	#ifdef DEBUG
	int i;
	#endif


	ARRAY_create(&EVAL->tree);


	current = EVAL->current;

	if (PATTERN_is_newline(*current) || PATTERN_is_end(*current))
		THROW(E_SYNTAX);

	analyze_expr(0, RS_NONE);

	while (PATTERN_is_newline(*current))
		current++;

	EVAL->current = current;

	#ifdef DEBUG
		printf("\n");
		for (i = 0; i < ARRAY_count(EVAL->tree); i++)
			READ_dump_pattern(&EVAL->tree[i]);
	#endif
}
