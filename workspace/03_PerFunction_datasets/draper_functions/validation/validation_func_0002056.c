collector_hantozen_flush(struct collector_hantozen_data *pc)
{
	int ret, n;

	ret = 0;
	if (pc->status) {
		n = (pc->cache - 0xff60) & 0x3f;
		if (pc->mode & 0x100) {
			ret = (*pc->next_filter->filter_function)(0x3000 + hankana2zenkata_table[n], pc->next_filter);
		} else if (pc->mode & 0x200) {
			ret = (*pc->next_filter->filter_function)(0x3000 + hankana2zenhira_table[n], pc->next_filter);
		}
		pc->status = 0;
	}

	return ret;
}
