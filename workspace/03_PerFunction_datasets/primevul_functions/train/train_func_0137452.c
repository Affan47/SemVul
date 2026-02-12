static void *aarp_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct aarp_entry *entry = v;
	struct aarp_iter_state *iter = seq->private;

	++*pos;


	if (v == SEQ_START_TOKEN)
		entry = iter_next(iter, NULL);


	else if (entry->next)
		entry = entry->next;


	else {
		++iter->bucket;
		entry = iter_next(iter, NULL);
	}
	return entry;
}
