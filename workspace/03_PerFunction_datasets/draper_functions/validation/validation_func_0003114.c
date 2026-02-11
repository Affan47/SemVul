ext_get_super(
		blkid_probe pr, uint32_t *fc, uint32_t *fi, uint32_t *frc)
{
	struct ext2_super_block *es;

	es = (struct ext2_super_block *)
			blkid_probe_get_buffer(pr, EXT_SB_OFF, 0x200);
	if (!es)
		return NULL;
	if (fc)
		*fc = le32_to_cpu(es->s_feature_compat);
	if (fi)
		*fi = le32_to_cpu(es->s_feature_incompat);
	if (frc)
		*frc = le32_to_cpu(es->s_feature_ro_compat);

	return es;
}
