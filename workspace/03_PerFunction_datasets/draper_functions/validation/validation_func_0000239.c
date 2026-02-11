DbEnv_lock_get(struct DbEnv *self,u_int32_t locker,u_int32_t flags,DBT *object,db_lockmode_t lock_mode){
		DB_LOCK *lock = NULL;
		if ((errno = __os_malloc(self->env, sizeof (DB_LOCK), &lock)) == 0)
			errno = self->lock_get(self, locker, flags, object,
			    lock_mode, lock);
		return lock;
	}
