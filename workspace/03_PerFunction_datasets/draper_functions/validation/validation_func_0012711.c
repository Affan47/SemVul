tifm_sd_read_fifo(struct tifm_sd *host, struct page *pg,
			      unsigned int off, unsigned int cnt)
{
	struct tifm_dev *sock = host->dev;
	unsigned char *buf;
	unsigned int pos = 0, val;

	buf = kmap_atomic(pg) + off;
	if (host->cmd_flags & DATA_CARRY) {
		buf[pos++] = host->bounce_buf_data[0];
		host->cmd_flags &= ~DATA_CARRY;
	}

	while (pos < cnt) {
		val = readl(sock->addr + SOCK_MMCSD_DATA);
		buf[pos++] = val & 0xff;
		if (pos == cnt) {
			host->bounce_buf_data[0] = (val >> 8) & 0xff;
			host->cmd_flags |= DATA_CARRY;
			break;
		}
		buf[pos++] = (val >> 8) & 0xff;
	}
	kunmap_atomic(buf - off);
}
