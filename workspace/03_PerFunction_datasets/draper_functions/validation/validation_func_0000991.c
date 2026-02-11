mono_disasm_code_one (MonoDisHelper *dh, MonoMethod *method, const guchar *ip, const guchar **endp)
{
	char *result;
	GString *res = g_string_new ("");

	if (!dh)
		dh = &default_dh;

	ip = dis_one (res, dh, method, ip, ip + 2);
	if (endp)
		*endp = ip;

	result = res->str;
	g_string_free (res, FALSE);
	return result;
}
