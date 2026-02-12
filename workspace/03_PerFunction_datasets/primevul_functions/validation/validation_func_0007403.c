static int effective_prio(const struct i915_request *rq)
{
	int prio = rq_prio(rq);


	if (i915_request_has_nopreempt(rq))
		prio = I915_PRIORITY_UNPREEMPTABLE;


	if (__i915_request_has_started(rq))
		prio |= I915_PRIORITY_NOSEMAPHORE;


	BUILD_BUG_ON(__NO_PREEMPTION & ~I915_PRIORITY_MASK);
	return prio | __NO_PREEMPTION;
}
