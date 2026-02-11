ath6kl_diag_write(struct ath6kl *ar, u32 address, void *data, u32 length)
{
	u32 count;
	__le32 *buf = data;
	int ret;

	if (WARN_ON(length % 4))
		return -EINVAL;

	for (count = 0; count < length / 4; count++, address += 4) {
		ret = ath6kl_diag_write32(ar, address, buf[count]);
		if (ret)
			return ret;
	}

	return 0;
}
