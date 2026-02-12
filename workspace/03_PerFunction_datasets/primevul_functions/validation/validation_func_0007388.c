ring_set_paused(const struct intel_engine_cs *engine, int state)
{


	engine->status_page.addr[I915_GEM_HWS_PREEMPT] = state;
	if (state)
		wmb();
}
