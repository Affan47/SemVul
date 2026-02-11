extract_flags(struct value_list **list, unsigned int *inv)
{
	unsigned int flags = 0;
	*inv = 0;

	struct value_list *entry, *tmp, *prev = NULL;
	list_for_each_safe(*list, entry, tmp) {
		int i;
		i = find_mnt_keyword(mnt_opts_table, entry->value);
		if (i != -1) {
			flags |= mnt_opts_table[i].set;
			*inv |= mnt_opts_table[i].clear;
			PDEBUG(" extracting mount flag %s req: 0x%x inv: 0x%x"
			       " => req: 0x%x inv: 0x%x\n",
			       entry->value, mnt_opts_table[i].set,
			       mnt_opts_table[i].clear, flags, *inv);
			if (prev)
				prev->next = tmp;
			if (entry == *list)
				*list = tmp;
			entry->next = NULL;
			free_value_list(entry);
		} else
			prev = entry;
	}

	return flags;
}
