static struct return_instance *find_next_ret_chain(struct return_instance *ri)
{
	bool chained;

	do {
		chained = ri->chained;
		ri = ri->next;
	} while (chained);

	return ri;
}
