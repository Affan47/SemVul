handle_worker(struct work_queue *q, struct link *l)
{
	char line[WORK_QUEUE_LINE_MAX];
	char key[WORK_QUEUE_LINE_MAX];
	struct work_queue_worker *w;

	link_to_hash_key(l, key);
	w = hash_table_lookup(q->worker_table, key);

	int keep_worker = 1;
	int result = recv_worker_msg(q, w, line, sizeof(line), time(0) + short_timeout);


	if(result > 0) {
		debug(D_WQ, "Invalid message from worker %s (%s): %s", w->hostname, w->addrport, line);
		keep_worker = 0;
	} else if(result < 0){
		debug(D_WQ, "Failed to read from worker %s (%s)", w->hostname, w->addrport);
		keep_worker = 0;
	}

	if(!keep_worker) {
		remove_worker(q, w);
	}
}
