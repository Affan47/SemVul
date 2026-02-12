virtual_bond_execute(struct i915_request *rq, struct dma_fence *signal)
{
	struct virtual_engine *ve = to_virtual_engine(rq->engine);
	intel_engine_mask_t allowed, exec;
	struct ve_bond *bond;

	allowed = ~to_request(signal)->engine->mask;

	bond = virtual_find_bond(ve, to_request(signal)->engine);
	if (bond)
		allowed &= bond->sibling_mask;


	exec = READ_ONCE(rq->execution_mask);
	while (!try_cmpxchg(&rq->execution_mask, &exec, exec & allowed))
		;


	to_request(signal)->execution_mask &= ~allowed;
}
