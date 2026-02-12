static inline bool need_preempt(const struct intel_engine_cs *engine,
				const struct i915_request *rq,
				struct rb_node *rb)
{
	int last_prio;

	if (!intel_engine_has_semaphores(engine))
		return false;


	last_prio = max(effective_prio(rq), I915_PRIORITY_NORMAL - 1);
	if (engine->execlists.queue_priority_hint <= last_prio)
		return false;


	if (!list_is_last(&rq->sched.link, &engine->active.requests) &&
	    rq_prio(list_next_entry(rq, sched.link)) > last_prio)
		return true;

	if (rb) {
		struct virtual_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);
		bool preempt = false;

		if (engine == ve->siblings[0]) {
			struct i915_request *next;

			rcu_read_lock();
			next = READ_ONCE(ve->request);
			if (next)
				preempt = rq_prio(next) > last_prio;
			rcu_read_unlock();
		}

		if (preempt)
			return preempt;
	}


	return queue_prio(&engine->execlists) > last_prio;
}
