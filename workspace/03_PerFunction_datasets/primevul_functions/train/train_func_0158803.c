void blk_start_plug(struct blk_plug *plug)
{
	struct task_struct *tsk = current;


	if (tsk->plug)
		return;

	INIT_LIST_HEAD(&plug->mq_list);
	INIT_LIST_HEAD(&plug->cb_list);
	plug->rq_count = 0;
	plug->multiple_queues = false;


	tsk->plug = plug;
}
