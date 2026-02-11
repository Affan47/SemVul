dlm_lockres_master_requery(struct dlm_ctxt *dlm,
				      struct dlm_lock_resource *res,
				      u8 *real_master)
{
	struct dlm_node_iter iter;
	int nodenum;
	int ret = 0;

	*real_master = DLM_LOCK_RES_OWNER_UNKNOWN;


	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	spin_unlock(&dlm->spinlock);

	while ((nodenum = dlm_node_iter_next(&iter)) >= 0) {

		if (nodenum == dlm->node_num)
			continue;
		ret = dlm_do_master_requery(dlm, res, nodenum, real_master);
		if (ret < 0) {
			mlog_errno(ret);
			if (!dlm_is_host_down(ret))
				BUG();


		}
		if (*real_master != DLM_LOCK_RES_OWNER_UNKNOWN) {
			mlog(0, "lock master is %u\n", *real_master);
			break;
		}
	}
	return ret;
}
