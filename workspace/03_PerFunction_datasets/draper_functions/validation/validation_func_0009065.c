probe_silraid(blkid_probe pr,
		const struct blkid_idmag *mag __attribute__((__unused__)))
{
	uint64_t off;
	struct silicon_metadata *sil;

	if (pr->size < 0x10000)
		return -1;
	if (!S_ISREG(pr->mode) && !blkid_probe_is_wholedisk(pr))
		return -1;

	off = ((pr->size / 0x200) - 1) * 0x200;

	sil = (struct silicon_metadata *)
			blkid_probe_get_buffer(pr, off,
				sizeof(struct silicon_metadata));
	if (!sil)
		return -1;

	if (le32_to_cpu(sil->magic) != SILICON_MAGIC)
		return -1;

	if (blkid_probe_sprintf_version(pr, "%u.%u",
				le16_to_cpu(sil->major_ver),
				le16_to_cpu(sil->minor_ver)) != 0)
		return -1;
	if (blkid_probe_set_magic(pr,
			off + offsetof(struct silicon_metadata, magic),
			sizeof(sil->magic),
			(unsigned char *) &sil->magic))
		return -1;
	return 0;
}
