static bool jbd2_write_access_granted(handle_t *handle, struct buffer_head *bh,
							bool undo)
{
	struct journal_head *jh;
	bool ret = false;


	if (buffer_dirty(bh))
		return false;


	rcu_read_lock();
	if (!buffer_jbd(bh))
		goto out;

	jh = READ_ONCE(bh->b_private);
	if (!jh)
		goto out;

	if (undo && !jh->b_committed_data)
		goto out;
	if (READ_ONCE(jh->b_transaction) != handle->h_transaction &&
	    READ_ONCE(jh->b_next_transaction) != handle->h_transaction)
		goto out;


	smp_mb();
	if (unlikely(jh->b_bh != bh))
		goto out;
	ret = true;
out:
	rcu_read_unlock();
	return ret;
}
