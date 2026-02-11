range_write_helper(void *key, void *data, void *ptr)
{
	__le32 buf[2];
	struct range_trans *rt = key;
	struct mls_range *r = data;
	struct policy_data *pd = ptr;
	void *fp = pd->fp;
	struct policydb *p = pd->p;
	int rc;

	buf[0] = cpu_to_le32(rt->source_type);
	buf[1] = cpu_to_le32(rt->target_type);
	rc = put_entry(buf, sizeof(u32), 2, fp);
	if (rc)
		return rc;
	if (p->policyvers >= POLICYDB_VERSION_RANGETRANS) {
		buf[0] = cpu_to_le32(rt->target_class);
		rc = put_entry(buf, sizeof(u32), 1, fp);
		if (rc)
			return rc;
	}
	rc = mls_write_range_helper(r, fp);
	if (rc)
		return rc;

	return 0;
}
