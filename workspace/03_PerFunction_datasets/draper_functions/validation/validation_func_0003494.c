tds_read_namelist(TDSSOCKET * tds, int remainder, struct namelist **p_head, int large)
{
	struct namelist *head = NULL, *cur = NULL, *prev;
	int num_names = 0;


	while (remainder > 0) {
		int namelen;

		prev = cur;
		if (!(cur = (struct namelist *) malloc(sizeof(struct namelist)))) {
			tds_free_namelist(head);
			return -1;
		}

		cur->next = NULL;
		if (prev)
			prev->next = cur;
		else
			head = cur;

		if (large) {
			namelen = tds_get_smallint(tds);
			remainder -= 2;
		} else {
			namelen = tds_get_byte(tds);
			--remainder;
		}

		if (tds_alloc_get_string(tds, &cur->name, namelen) < 0) {
			tds_free_namelist(head);
			return -1;
		}

		remainder -= namelen;
		if (IS_TDS7_PLUS(tds))
			remainder -= namelen;
		num_names++;
	}

	*p_head = head;
	return num_names;
}
