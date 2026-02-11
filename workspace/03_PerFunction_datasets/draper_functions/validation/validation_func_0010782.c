ok(int res)
{
	static char buf[100];

	if (res == ENOTTY) {
		strcpy(buf, "OK (Not Supported)");
		res = 0;
	} else {
		strcpy(buf, "OK");
	}
	tests_total++;
	if (res) {
		app_result = res;
		sprintf(buf, "FAIL");
	} else {
		tests_ok++;
	}
	return buf;
}
