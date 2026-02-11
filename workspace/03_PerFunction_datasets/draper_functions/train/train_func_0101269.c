dlm_kick_thread(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	if (res) {
		spin_lock(&dlm->spinlock);
		spin_lock(&res->spinlock);
		__dlm_dirty_lockres(dlm, res);
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
	}
	wake_up(&dlm->dlm_thread_wq);
}
