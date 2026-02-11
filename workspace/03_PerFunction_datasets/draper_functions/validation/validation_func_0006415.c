isns_attr_list_get_uint32(const isns_attr_list_t *list,
		uint32_t tag, uint32_t *value)
{
	isns_attr_t	*attr;

	if (!(attr = __isns_attr_list_find(list, tag))
	 || !ISNS_ATTR_IS_UINT32(attr))
		return 0;

	*value = attr->ia_value.iv_uint32;
	return 1;
}
