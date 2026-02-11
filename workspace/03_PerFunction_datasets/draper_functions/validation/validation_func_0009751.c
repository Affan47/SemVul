qib_sd7220_prog_ld(struct qib_devdata *dd, int sdnum,
			      const u8 *img, int len, int offset)
{
	int cnt, sofar, req;

	sofar = 0;
	while (sofar < len) {
		req = len - sofar;
		if (req > PROG_CHUNK)
			req = PROG_CHUNK;
		cnt = qib_sd7220_ram_xfer(dd, sdnum, offset + sofar,
					  (u8 *)img + sofar, req, 0);
		if (cnt < req) {
			sofar = -1;
			break;
		}
		sofar += req;
	}
	return sofar;
}
