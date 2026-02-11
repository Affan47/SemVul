visorchannel_clear(struct visorchannel *channel, ulong offset, u8 ch,
		   ulong nbytes)
{
	int err;
	int bufsize = PAGE_SIZE;
	int written = 0;
	u8 *buf;

	buf = (u8 *)__get_free_page(GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	memset(buf, ch, bufsize);

	while (nbytes > 0) {
		int thisbytes = bufsize;

		if (nbytes < thisbytes)
			thisbytes = nbytes;
		err = visorchannel_write(channel, offset + written,
					 buf, thisbytes);
		if (err)
			goto cleanup;

		written += thisbytes;
		nbytes -= thisbytes;
	}
	err = 0;

cleanup:
	free_page((unsigned long)buf);
	return err;
}
