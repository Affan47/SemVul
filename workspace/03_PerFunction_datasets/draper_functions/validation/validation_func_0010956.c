swan_vk_match_key(const char *keyname, const struct swan_vk_descriptor *descs, size_t size)
{
	const struct swan_vk_descriptor *desc_end;

	for (desc_end = descs + size; descs < desc_end && text_lhcmp(keyname, descs->name); descs++);

	if (descs < desc_end)
	{
		return descs;
	}

	return NULL;
}
