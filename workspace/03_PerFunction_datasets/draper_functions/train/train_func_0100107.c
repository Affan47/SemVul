stktable_touch(struct stktable *t, struct stksess *ts, int local)
{
	struct eb32_node * eb;
	ts->expire = tick_add(now_ms, MS_TO_TICKS(t->expire));
	if (t->expire) {
		t->exp_task->expire = t->exp_next = tick_first(ts->expire, t->exp_next);
		task_queue(t->exp_task);
	}

	if (t->sync_task && local) {
		ts->upd.key = ++t->update;
		t->localupdate = t->update;
		eb32_delete(&ts->upd);
		eb = eb32_insert(&t->updates, &ts->upd);
		if (eb != &ts->upd)  {
			eb32_delete(eb);
			eb32_insert(&t->updates, &ts->upd);
		}
		task_wakeup(t->sync_task, TASK_WOKEN_MSG);
	}
	return ts;
}
