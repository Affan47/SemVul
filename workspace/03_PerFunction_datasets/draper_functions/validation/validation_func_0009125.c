cmd_cancel_scan (SANE_Handle handle)
{
	KodakAio_Scanner *s = (KodakAio_Scanner *) handle;
	unsigned char reply[8];

	if (strcmp(source_list[s->val[OPT_SOURCE].w], ADF_STR) == 0) {
		if (kodakaio_txrxack(s, KodakEsp_F, reply)!= SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;
		if (kodakaio_txrxack(s, KodakEsp_UnLock, reply)!= SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;
		DBG(5, "%s unlocked the scanner with adf F U\n", __func__);
	}
	else {
		if (kodakaio_txrxack(s, KodakEsp_UnLock, reply)!= SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;
		DBG(5, "%s unlocked the scanner U\n", __func__);
	}
	s->scanning = SANE_FALSE;
	return SANE_STATUS_GOOD;
}
