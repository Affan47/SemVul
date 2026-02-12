static void execlists_context_reset(struct intel_context *ce)
{


	intel_ring_reset(ce->ring, 0);
	__execlists_update_reg_state(ce, ce->engine);
}
