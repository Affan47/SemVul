isns_attr_type_opaque_match(const isns_value_t *a, const isns_value_t *b)
{
	if (a->iv_opaque.len != b->iv_opaque.len)
		return 0;
	return !memcmp(a->iv_opaque.ptr, b->iv_opaque.ptr, a->iv_opaque.len);
}
