verify_constant_tag(struct verifier_context *vrf, enum cafebabe_constant_tag tag, unsigned int index)
{
	const struct cafebabe_class *class = vrf->method->class->class;

	if (index >= class->constant_pool_count)
		return vrf_err("Invalid reference to constant %u.\n", index), E_WRONG_CONSTANT_POOL_INDEX;

	if (class->constant_pool[index].tag != tag)
		return E_TYPE_CHECKING;

	return 0;
}
