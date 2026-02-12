execlists_context_status_change(struct i915_request *rq, unsigned long status)
{


	if (!IS_ENABLED(CONFIG_DRM_I915_GVT))
		return;

	atomic_notifier_call_chain(&rq->engine->context_status_notifier,
				   status, rq);
}
