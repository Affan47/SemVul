jffs2_verify_write(struct jffs2_sb_info *c, unsigned char *buf,
			      uint32_t ofs)
{
	int ret;
	size_t retlen;
	char *eccstr;

	ret = mtd_read(c->mtd, ofs, c->wbuf_pagesize, &retlen, c->wbuf_verify);
	if (ret && ret != -EUCLEAN && ret != -EBADMSG) {
		pr_warn("%s(): Read back of page at %08x failed: %d\n",
			__func__, c->wbuf_ofs, ret);
		return ret;
	} else if (retlen != c->wbuf_pagesize) {
		pr_warn("%s(): Read back of page at %08x gave short read: %zd not %d\n",
			__func__, ofs, retlen, c->wbuf_pagesize);
		return -EIO;
	}
	if (!memcmp(buf, c->wbuf_verify, c->wbuf_pagesize))
		return 0;

	if (ret == -EUCLEAN)
		eccstr = "corrected";
	else if (ret == -EBADMSG)
		eccstr = "correction failed";
	else
		eccstr = "OK or unused";

	pr_warn("Write verify error (ECC %s) at %08x. Wrote:\n",
		eccstr, c->wbuf_ofs);
	print_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1,
		       c->wbuf, c->wbuf_pagesize, 0);

	pr_warn("Read back:\n");
	print_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1,
		       c->wbuf_verify, c->wbuf_pagesize, 0);

	return -EIO;
}
