init_parameters_from_args(F_PARAMETERS *p, int argc, F_CHAR **argv)
{
	default_parameters(p);
	p->executable_path = argv[0];

	int i = 0;

	for(i = 1; i < argc; i++)
	{
		if(factor_arg(argv[i],STRING_LITERAL("-datastack=%d"),&p->ds_size));
		else if(factor_arg(argv[i],STRING_LITERAL("-retainstack=%d"),&p->rs_size));
		else if(factor_arg(argv[i],STRING_LITERAL("-generations=%d"),&p->gen_count));
		else if(factor_arg(argv[i],STRING_LITERAL("-young=%d"),&p->young_size));
		else if(factor_arg(argv[i],STRING_LITERAL("-aging=%d"),&p->aging_size));
		else if(factor_arg(argv[i],STRING_LITERAL("-tenured=%d"),&p->tenured_size));
		else if(factor_arg(argv[i],STRING_LITERAL("-codeheap=%d"),&p->code_size));
		else if(STRCMP(argv[i],STRING_LITERAL("-securegc")) == 0) p->secure_gc = true;
		else if(STRCMP(argv[i],STRING_LITERAL("-fep")) == 0) p->fep = true;
		else if(STRNCMP(argv[i],STRING_LITERAL("-i="),3) == 0) p->image_path = argv[i] + 3;
		else if(STRCMP(argv[i],STRING_LITERAL("-console")) == 0) p->console = true;
		else if(STRCMP(argv[i],STRING_LITERAL("-no-stack-traces")) == 0) p->stack_traces = false;
	}
}
