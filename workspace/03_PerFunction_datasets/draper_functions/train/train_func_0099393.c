_raw_spin_lock_nested(raw_spinlock_t *lock, int subclass)
{
	preempt_disable();
	spin_acquire(&lock->dep_map, subclass, 0, _RET_IP_);
	LOCK_CONTENDED(lock, do_raw_spin_trylock, do_raw_spin_lock);
}
