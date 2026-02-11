import_func_name(const char *dllname, const char *funcname, int ordinal)
{
	char res[1024];
	if (funcname) {
		ht_snprintf(res, sizeof res, "%s:%s", dllname, funcname);

	} else {
		ht_snprintf(res, sizeof res, "%s:%04x", dllname, ordinal);
	}
	return ht_strdup(res);
}
