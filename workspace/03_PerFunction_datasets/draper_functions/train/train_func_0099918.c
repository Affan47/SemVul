cmd_start_scan (SANE_Handle handle, size_t expect_total)

{
	KodakAio_Scanner *s = (KodakAio_Scanner *) handle;
	SANE_Status status = SANE_STATUS_GOOD;
	unsigned char reply[8];


	if (strcmp(source_list[s->val[OPT_SOURCE].w], ADF_STR) == 0) {
		if (! s->adf_loaded) return SANE_STATUS_CANCELLED;
		if (kodakaio_txrxack(s, KodakEsp_F, reply)!= SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;
	}

	if (kodakaio_txrxack(s, KodakEsp_E, reply)!= SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;

	print_status(s, 5);
	DBG(32, "at 942 starting the scan, expected total bytes %d\n",expect_total);
	k_send(s, KodakEsp_Go, 8, &status);

	if (status != SANE_STATUS_GOOD)
		DBG(8, "%s: Data NOT successfully sent\n", __func__);
	else {
		DBG(8, "%s: Data successfully sent\n", __func__);
		s->scanning = SANE_TRUE;
	}
	return status;
}
