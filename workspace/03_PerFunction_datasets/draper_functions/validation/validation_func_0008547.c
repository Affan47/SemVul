validate_type_bytes (const struct Opt * opt,
                     const char * value,
                     const guint32 len)
{
	guint32 check_len;

	g_return_val_if_fail (opt != NULL, FALSE);
	g_return_val_if_fail (value != NULL, FALSE);

	check_len = opt->int_high ? opt->int_high : 255;
	if (len > check_len)
		return FALSE;

	return TRUE;
}
