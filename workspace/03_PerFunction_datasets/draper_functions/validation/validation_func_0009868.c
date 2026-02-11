fmt_bytes(struct cli *cli, ssize_t t)
{
	const char *p;

	if (t & 0xff) {
		VCLI_Out(cli, "%zub", t);
		return;
	}
	for (p = "kMGTPEZY"; *p; p++) {
		if (t & 0x300) {
			VCLI_Out(cli, "%.2f%c", t / 1024.0, *p);
			return;
		}
		t /= 1024;
		if (t & 0x0ff) {
			VCLI_Out(cli, "%zu%c", t, *p);
			return;
		}
	}
	VCLI_Out(cli, "(bogus number)");
}
