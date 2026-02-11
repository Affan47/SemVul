close_stack( struct stack_item	*stack, u_64 thispid, u_64 cyc_time )
	{
	unsigned long	code;

	fprintf(stdbug, "close stack for pid %4"PRId64", pos %u, cyc_time %"PRIu64"\n",
		thispid, stack->pos, cyc_time);

	if( stack->pos > 0 && stack->code[stack->pos] == FXT_SWITCH_TO_CODE )
		{

		cyc_time = stack->lastreltime;
		stack->pos--;
		}

	while( stack->pos > 0 )
		{

		code = stack->code[stack->pos];
		fprintf(stdbug, "v3[%u] ", stack->pos);
		if( trace_space == FXT_SPACE_KERNEL && code < FKT_UNSHIFTED_LIMIT_CODE )
			{
			int				z, should_be_hex;
			char			category;
			const char		*name;
			z = fkt_find_syscall(fxt,code, &category, &name, &should_be_hex);
			fprintf(stdbug, "%c ", category);
			if( should_be_hex )
				fprintf(stdbug, "%04x", z);
			else
				fprintf(stdbug, "%4d", z);
			fprintf(stdbug, " %08lx %28s\n", code, name);
			}
		else
			fprintf(stdbug, "%13s %08lx %28s\n",
				"function", code, find_name(code,1,-1));


		stack->pos--;
		}

	stack->user_cycles = cyc_time-stack->start_cycle[0];

	fprintf(stdbug, "pid %4"PRId64" process cycles %"PRIu64"\n\n",
		thispid, stack->user_cycles);
	}
