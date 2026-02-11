ocfs2_remove_lockres_tracking(struct ocfs2_lock_res *res)
{
	spin_lock(&ocfs2_dlm_tracking_lock);
	if (!list_empty(&res->l_debug_list))
		list_del_init(&res->l_debug_list);
	spin_unlock(&ocfs2_dlm_tracking_lock);
}
