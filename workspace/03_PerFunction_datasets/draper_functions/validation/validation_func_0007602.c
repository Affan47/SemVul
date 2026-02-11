ocfs2_dlm_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct ocfs2_dlm_seq_priv *priv = m->private;
	struct ocfs2_lock_res *iter = v;
	struct ocfs2_lock_res *dummy = &priv->p_iter_res;

	spin_lock(&ocfs2_dlm_tracking_lock);
	iter = ocfs2_dlm_next_res(iter, priv);
	list_del_init(&dummy->l_debug_list);
	if (iter) {
		list_add(&dummy->l_debug_list, &iter->l_debug_list);
		priv->p_tmp_res = *iter;
		iter = &priv->p_tmp_res;
	}
	spin_unlock(&ocfs2_dlm_tracking_lock);

	return iter;
}
