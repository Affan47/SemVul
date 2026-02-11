usbtr_recv(transport_t tr_base, uint8_t *databuf, int max_len)
{
	struct rf2500_transport *tr = (struct rf2500_transport *)tr_base;
	int rlen;

	if (tr->offset >= tr->len) {
		if (usb_bulk_read(tr->handle, USB_FET_IN_EP,
				(char *)tr->buf, sizeof(tr->buf),
				10000) < 0) {
			pr_error("rf2500: can't receive data");
			return -1;
		}

#ifdef DEBUG_USBTR
		debug_hexdump("USB transfer in", tr->buf, 64);
#endif

		tr->len = tr->buf[1] + 2;
		if (tr->len > sizeof(tr->buf))
			tr->len = sizeof(tr->buf);
		tr->offset = 2;
	}

	rlen = tr->len - tr->offset;
	if (rlen > max_len)
		rlen = max_len;
	memcpy(databuf, tr->buf + tr->offset, rlen);
	tr->offset += rlen;

	return rlen;
}
