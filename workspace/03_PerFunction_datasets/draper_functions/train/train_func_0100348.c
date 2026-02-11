mtdswap_readsect(struct mtd_blktrans_dev *dev,
			unsigned long page, char *buf)
{
	struct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	struct mtd_info *mtd = d->mtd;
	unsigned int realblock, retries;
	loff_t readpos;
	struct swap_eb *eb;
	size_t retlen;
	int ret;

	d->sect_read_count++;

	if (header) {
		if (unlikely(page == 0))
			return mtdswap_auto_header(d, buf);

		page--;
	}

	realblock = d->page_data[page];
	if (realblock > BLOCK_MAX) {
		memset(buf, 0x0, PAGE_SIZE);
		if (realblock == BLOCK_UNDEF)
			return 0;
		else
			return -EIO;
	}

	eb = d->eb_data + (realblock / d->pages_per_eblk);
	BUG_ON(d->revmap[realblock] == PAGE_UNDEF);

	readpos = (loff_t)realblock << PAGE_SHIFT;
	retries = 0;

retry:
	ret = mtd_read(mtd, readpos, PAGE_SIZE, &retlen, buf);

	d->mtd_read_count++;
	if (mtd_is_bitflip(ret)) {
		eb->flags |= EBLOCK_BITFLIP;
		mtdswap_rb_add(d, eb, MTDSWAP_BITFLIP);
		ret = 0;
	}

	if (ret < 0) {
		dev_err(d->dev, "Read error %d\n", ret);
		eb->flags |= EBLOCK_READERR;
		mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
		retries++;
		if (retries < MTDSWAP_IO_RETRIES)
			goto retry;

		return ret;
	}

	if (retlen != PAGE_SIZE) {
		dev_err(d->dev, "Short read %zd\n", retlen);
		return -EIO;
	}

	return 0;
}
