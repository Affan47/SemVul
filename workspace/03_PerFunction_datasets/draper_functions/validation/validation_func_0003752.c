ParseNotAvailInterworking(struct Aoc *chanp, u_char *p, u_char *end, char *str)
{
	int ret;

	ret = ParseNull(chanp, p, end, -1);
	if (ret < 0)
		return ret;
	strcpy(str, "(not available)");
	return ret;
}
