TS_find_name(STACK_OF(GENERAL_NAME) *gen_names, GENERAL_NAME *name)
	{
	int i, found;
	for (i = 0, found = 0; !found && i < sk_GENERAL_NAME_num(gen_names);
	     ++i)
		{
		GENERAL_NAME *current = sk_GENERAL_NAME_value(gen_names, i);
		found = GENERAL_NAME_cmp(current, name) == 0;
		}
	return found ? i - 1 : -1;
	}
