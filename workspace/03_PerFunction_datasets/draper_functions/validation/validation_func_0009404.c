excel_write_WRITEACCESS (BiffPut *bp)
{
	guint8   pad [112];
	unsigned len;
	char const *utf8_name = go_get_real_name ();

	if (utf8_name == NULL)
		utf8_name = "";

	ms_biff_put_var_next (bp, BIFF_WRITEACCESS);
	if (bp->version >= MS_BIFF_V8) {
		len = excel_write_string (bp, STR_TWO_BYTE_LENGTH, utf8_name);
		memset (pad, ' ', sizeof pad);
		ms_biff_put_var_write (bp, pad, sizeof pad - len);
		ms_biff_put_commit (bp);
	} else {
		len = excel_write_string (bp, STR_ONE_BYTE_LENGTH, utf8_name);
		memset (pad, ' ', 32);
		ms_biff_put_var_write (bp, pad, 32 - len - 1);
		ms_biff_put_commit (bp);
	}
}
