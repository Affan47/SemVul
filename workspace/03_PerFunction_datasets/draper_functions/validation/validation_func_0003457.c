iscsi_target_destroy(int tid)
{
	struct iscsi_target* target;

	target = target_find_by_id(tid);
	if (!target) {
		eprintf("can't find the target %d\n", tid);
		return;
	}

	if (target->nr_sessions) {
		eprintf("the target %d still has sessions\n", tid);
		return;
	}
	if (!list_empty(&target->sessions_list)) {
		eprintf("bug still have sessions %d\n", tid);
		exit(-1);
	}

	list_del(&target->tlist);
	if (target->redirect_info.callback)
		free(target->redirect_info.callback);
	free(target);
	isns_target_deregister(tgt_targetname(tid));

	return;
}
