option_chain_head_dereference (ptr, file, line)
	struct option_chain_head **ptr;
	const char *file;
	int line;
{
	struct option_chain_head *option_chain_head;
	pair car, cdr;

	if (!ptr || !*ptr) {
		log_error ("%s(%d): null pointer", file, line);
#if defined (POINTER_DEBUG)
		abort ();
#else
		return 0;
#endif
	}

	option_chain_head = *ptr;
	*ptr = (struct option_chain_head *)0;
	--option_chain_head -> refcnt;
	rc_register (file, line, ptr, option_chain_head,
		     option_chain_head -> refcnt, 1, RC_MISC);
	if (option_chain_head -> refcnt > 0)
		return 1;

	if (option_chain_head -> refcnt < 0) {
		log_error ("%s(%d): negative refcnt!", file, line);
#if defined (DEBUG_RC_HISTORY)
		dump_rc_history (option_chain_head);
#endif
#if defined (POINTER_DEBUG)
		abort ();
#else
		return 0;
#endif
	}


	for (car = option_chain_head -> first; car; car = cdr) {
		cdr = car -> cdr;
		if (car -> car)
			option_cache_dereference ((struct option_cache **)
						  (&car -> car), MDL);
		dfree (car, MDL);
		car = cdr;
	}

	dfree (option_chain_head, file, line);
	return 1;
}
