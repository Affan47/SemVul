bl_up_read(struct block_lock *lock)
{
	spin_lock(&lock->lock);
	BUG_ON(lock->count <= 0);
	__del_holder(lock, current);
	--lock->count;
	if (!list_empty(&lock->waiters))
		__wake_many(lock);
	spin_unlock(&lock->lock);
}
