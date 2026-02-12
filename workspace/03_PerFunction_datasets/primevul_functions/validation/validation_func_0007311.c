assert_priority_queue(const struct i915_request *prev,
		      const struct i915_request *next)
{


	if (i915_request_is_active(prev))
		return true;

	return rq_prio(prev) >= rq_prio(next);
}
