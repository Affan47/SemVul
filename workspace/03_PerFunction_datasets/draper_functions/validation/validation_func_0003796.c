debug_rt_mutex_unlock(struct rt_mutex *lock)
{
	DEBUG_LOCKS_WARN_ON(rt_mutex_owner(lock) != current);
}
