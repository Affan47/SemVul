static void firebird_info_cb(void *arg, char const *s)
{
	if (arg) {
		if (*(char*)arg) {
			strcat(arg, " ");
		}
		strcat(arg, s);
	}
}
