void perf_event_free_task(struct task_struct *task)
{
	struct perf_event_context *ctx;
	struct perf_event *event, *tmp;
	int ctxn;

	for_each_task_context_nr(ctxn) {
		ctx = task->perf_event_ctxp[ctxn];
		if (!ctx)
			continue;

		mutex_lock(&ctx->mutex);
		raw_spin_lock_irq(&ctx->lock);


		RCU_INIT_POINTER(task->perf_event_ctxp[ctxn], NULL);
		WRITE_ONCE(ctx->task, TASK_TOMBSTONE);
		put_task_struct(task);
		raw_spin_unlock_irq(&ctx->lock);

		list_for_each_entry_safe(event, tmp, &ctx->event_list, event_entry)
			perf_free_event(event, ctx);

		mutex_unlock(&ctx->mutex);


		wait_var_event(&ctx->refcount, refcount_read(&ctx->refcount) == 1);
		put_ctx(ctx);
	}
}
