static unsigned long active_preempt_timeout(struct intel_engine_cs *engine)
{
	struct i915_request *rq;

	rq = last_active(&engine->execlists);
	if (!rq)
		return 0;


	if (unlikely(i915_gem_context_is_banned(rq->gem_context)))
		return 1;

	return READ_ONCE(engine->props.preempt_timeout_ms);
}
