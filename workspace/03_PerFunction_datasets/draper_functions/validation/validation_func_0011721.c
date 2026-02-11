coda_cache_check(struct inode *inode, int mask)
{
	struct coda_inode_info *cii = ITOC(inode);
	int hit;

	spin_lock(&cii->c_lock);
	hit = (mask & cii->c_cached_perm) == mask &&
	    uid_eq(cii->c_uid, current_fsuid()) &&
	    cii->c_cached_epoch == atomic_read(&permission_epoch);
	spin_unlock(&cii->c_lock);

	return hit;
}
