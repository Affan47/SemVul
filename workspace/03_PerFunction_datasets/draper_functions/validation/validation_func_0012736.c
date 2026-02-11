gtt_task_new_insert (GttTask *old)
{
	int is_running = 0;
	GttProject *prj;
	GttTask *task;
	int idx;

	if (!old) return NULL;

	task = gtt_task_new();


	task->billable = old->billable;
	task->billrate = old->billrate;
	task->billstatus = old->billstatus;
	task->bill_unit = old->bill_unit;
	task->interval_list = NULL;


	prj = old->parent;
	task->parent = prj;
	if (!prj) return task;


	is_running = task_suspend (old);

	idx = g_list_index (prj->task_list, old);
	prj->task_list = g_list_insert (prj->task_list, task, idx);

	if (is_running) gtt_project_timer_start (prj);
	proj_refresh_time (prj);
	return task;
}
