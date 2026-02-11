conf_call_set(char *item, conf_parm_t * value, int type)
{
	conf_parm_t *cp;
	cp = value->v.list;

	if(value->type & CF_FLIST)
	{
		add_entry_flist(curconf, item, value->v.list);
		return 0;
	}

	for(; cp != NULL; cp = cp->next)
	{
		switch (CF_TYPE(cp->type))
		{
		case CF_STRING:
		case CF_QSTRING:
			add_entry(curconf, item, (void *)cp->v.string, cp->type);
			break;
		case CF_TIME:
		case CF_INT:
		case CF_YESNO:
			add_entry(curconf, item, (void *)(unsigned long)cp->v.number, cp->type);
			break;
		case CF_LIST:
			break;
		default:
			break;

		}
	}

	return 0;
}
