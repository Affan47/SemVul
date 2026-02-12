__execlists_schedule_out(struct i915_request *rq,
			 struct intel_engine_cs * const engine)
{
	struct intel_context * const ce = rq->hw_context;


	if (list_is_last(&rq->link, &ce->timeline->requests) &&
	    i915_request_completed(rq))
		intel_engine_add_retire(engine, ce->timeline);

	intel_engine_context_out(engine);
	execlists_context_status_change(rq, INTEL_CONTEXT_SCHEDULE_OUT);
	intel_gt_pm_put_async(engine->gt);


	if (ce->engine != engine)
		kick_siblings(rq, ce);

	intel_context_put(ce);
}
