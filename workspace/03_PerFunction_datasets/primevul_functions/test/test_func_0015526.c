static const char *typeString(ut32 n, int *bits) {
	*bits = 32;
	if (n == 12) {
		return "arm";
	}
	if (n == 0x0100000c) {
		*bits = 64;
		return "arm";
	}
	if (n == 0x0200000c) {

		*bits = 64;
		return "arm";
	}
	return "x86";
}
