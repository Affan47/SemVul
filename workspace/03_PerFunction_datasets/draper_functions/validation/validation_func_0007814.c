lvm2_image(const void *buf, unsigned long long *blocks)
{
	const struct lvm2_super_block *lsb;
	int i;


	for (i = 0; i < BLOCK_SIZE; i += 0x200) {
		lsb = (const struct lvm2_super_block *)(buf + i);

		if (!memcmp(lsb->magic, LVM2_MAGIC, LVM2_MAGIC_L) &&
		    !memcmp(lsb->type, LVM2_TYPE, LVM2_TYPE_L)) {

			*blocks = 0;
			return 1;
		}
	}

	return 0;
}
