static u32 *gen8_emit_wa_tail(struct i915_request *request, u32 *cs)
{

	*cs++ = MI_ARB_CHECK;
	*cs++ = MI_NOOP;
	request->wa_tail = intel_ring_offset(request, cs);

	return cs;
}
