queue_member_follower_removal(struct call_queue *queue, struct member *mem)
{
	int pos = mem->queuepos;


	if (pos < queue->rrpos) {
		queue->rrpos--;
	}

	ao2_callback(queue->members, OBJ_NODATA | OBJ_MULTIPLE, queue_member_decrement_followers, &pos);
}
