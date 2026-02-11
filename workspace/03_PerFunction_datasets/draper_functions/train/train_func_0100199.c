brasero_async_task_manager_thread (BraseroAsyncTaskManager *self)
{
	gboolean result;
	GCancellable *cancel;
	BraseroAsyncTaskCtx *ctx;

	cancel = g_cancellable_new ();

	g_mutex_lock (self->priv->lock);

	while (1) {
		BraseroAsyncTaskResult res;


		self->priv->unused_threads ++;


		while (!self->priv->waiting_tasks) {
			if (self->priv->cancelled)
				goto end;


			if (self->priv->num_threads - self->priv->unused_threads > 0) {
				GTimeVal timeout;


				g_get_current_time (&timeout);
				g_time_val_add (&timeout, 5000000);
				result = g_cond_timed_wait (self->priv->new_task,
							    self->priv->lock,
							    &timeout);

				if (!result)
					goto end;
			}
			else
				g_cond_wait (self->priv->new_task,
					     self->priv->lock);
		}


		self->priv->unused_threads --;


		ctx = self->priv->waiting_tasks->data;
		ctx->cancel = cancel;
		ctx->priority &= ~BRASERO_ASYNC_RESCHEDULE;

		self->priv->waiting_tasks = g_slist_remove (self->priv->waiting_tasks, ctx);
		self->priv->active_tasks = g_slist_prepend (self->priv->active_tasks, ctx);

		g_mutex_unlock (self->priv->lock);
		res = ctx->type->thread (self, cancel, ctx->data);
		g_mutex_lock (self->priv->lock);


		self->priv->active_tasks = g_slist_remove (self->priv->active_tasks, ctx);
		g_cond_signal (self->priv->task_finished);


		if (!g_cancellable_is_cancelled (cancel)) {
			if (res == BRASERO_ASYNC_TASK_RESCHEDULE) {
				if (self->priv->waiting_tasks) {
					BraseroAsyncTaskCtx *next;

					next = self->priv->waiting_tasks->data;
					if (next->priority > ctx->priority)
						brasero_async_task_manager_insert_task (self, ctx);
					else
						self->priv->waiting_tasks = g_slist_prepend (self->priv->waiting_tasks, ctx);
				}
				else
					self->priv->waiting_tasks = g_slist_prepend (self->priv->waiting_tasks, ctx);
			}
			else {
				if (ctx->type->destroy)
					ctx->type->destroy (self, FALSE, ctx->data);
				g_free (ctx);
			}
		}
		else
			g_cancellable_reset (cancel);
	}

end:

	self->priv->unused_threads --;
	self->priv->num_threads --;


	g_cond_signal (self->priv->thread_finished);
	g_mutex_unlock (self->priv->lock);

	g_object_unref (cancel);

	g_thread_exit (NULL);

	return NULL;
}
