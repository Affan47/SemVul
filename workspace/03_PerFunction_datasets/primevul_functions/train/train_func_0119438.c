int send_xattr(int f, stat_x *sxp)
{
	int ndx = find_matching_xattr(sxp->xattr);


	write_varint(f, ndx + 1);

	if (ndx < 0) {
		rsync_xa *rxa;
		int count = sxp->xattr->count;
		write_varint(f, count);
		for (rxa = sxp->xattr->items; count--; rxa++) {
			size_t name_len = rxa->name_len;
			const char *name = rxa->name;

			if (name_len > RPRE_LEN
#ifdef HAVE_LINUX_XATTRS
			 && am_root < 0
#endif
			 && name[RPRE_LEN] != '%' && HAS_PREFIX(name, RSYNC_PREFIX)) {
				name += RPRE_LEN;
				name_len -= RPRE_LEN;
			}
#ifndef HAVE_LINUX_XATTRS
			else {

				name_len += UPRE_LEN;
			}
#endif
			write_varint(f, name_len);
			write_varint(f, rxa->datum_len);
#ifndef HAVE_LINUX_XATTRS
			if (name_len > rxa->name_len) {
				write_buf(f, USER_PREFIX, UPRE_LEN);
				name_len -= UPRE_LEN;
			}
#endif
			write_buf(f, name, name_len);
			if (rxa->datum_len > MAX_FULL_DATUM)
				write_buf(f, rxa->datum + 1, MAX_DIGEST_LEN);
			else
				write_bigbuf(f, rxa->datum, rxa->datum_len);
		}
		ndx = rsync_xal_store(sxp->xattr);
	}

	return ndx;
}
