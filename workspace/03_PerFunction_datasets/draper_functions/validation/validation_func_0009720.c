cachefiles_delete_object(struct cachefiles_cache *cache,
			     struct cachefiles_object *object)
{
	struct dentry *dir;
	int ret;

	_enter(",OBJ%x{%p}", object->fscache.debug_id, object->dentry);

	ASSERT(object->dentry);
	ASSERT(d_backing_inode(object->dentry));
	ASSERT(object->dentry->d_parent);

	dir = dget_parent(object->dentry);

	mutex_lock_nested(&d_inode(dir)->i_mutex, I_MUTEX_PARENT);

	if (test_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->fscache.flags)) {


		_debug("object preemptively buried");
		mutex_unlock(&d_inode(dir)->i_mutex);
		ret = 0;
	} else {


		if (dir == object->dentry->d_parent) {
			ret = cachefiles_bury_object(cache, dir,
						     object->dentry, false,
						     FSCACHE_OBJECT_WAS_RETIRED);
		} else {


			mutex_unlock(&d_inode(dir)->i_mutex);
			ret = 0;
		}
	}

	dput(dir);
	_leave(" = %d", ret);
	return ret;
}
