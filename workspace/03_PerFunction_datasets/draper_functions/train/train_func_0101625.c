xmmsv_build_dict (const char *firstkey, ...)
{
	va_list ap;
	const char *key;
	xmmsv_t *val, *res;

	res = xmmsv_new_dict ();
	if (!res)
		return NULL;

	va_start (ap, firstkey);

	key = firstkey;
	do {
		val = va_arg (ap, xmmsv_t *);

		if (!xmmsv_dict_set (res, key, val)) {
			xmmsv_unref (res);
			res = NULL;
			break;
		}
		xmmsv_unref (val);
		key = va_arg (ap, const char *);
	} while (key);

	va_end (ap);

	return res;
}
