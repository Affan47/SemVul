get_this_config(struct ddf1 *ddf1, uint64_t offset)
{
	struct ddf1_phys_drive *pd = get_phys_drive(ddf1);
	int i = get_config_byoffset(ddf1, pd, offset);

	return i < 0 ? NULL : get_config(ddf1, pd, i);
}
