static bool can_merge_rq(const struct i915_request *prev,
			 const struct i915_request *next)
{
	GEM_BUG_ON(prev == next);
	GEM_BUG_ON(!assert_priority_queue(prev, next));


	if (i915_request_completed(next))
		return true;

	if (unlikely((prev->flags ^ next->flags) &
		     (I915_REQUEST_NOPREEMPT | I915_REQUEST_SENTINEL)))
		return false;

	if (!can_merge_ctx(prev->hw_context, next->hw_context))
		return false;

	return true;
}
