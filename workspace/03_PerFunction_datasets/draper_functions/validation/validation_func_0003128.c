snd_seq_queue_alloc(int client, int locked, unsigned int info_flags)
{
	struct snd_seq_queue *q;

	q = queue_new(client, locked);
	if (q == NULL)
		return ERR_PTR(-ENOMEM);
	q->info_flags = info_flags;
	queue_use(q, client, 1);
	snd_use_lock_use(&q->use_lock);
	if (queue_list_add(q) < 0) {
		snd_use_lock_free(&q->use_lock);
		queue_delete(q);
		return ERR_PTR(-ENOMEM);
	}
	return q;
}
