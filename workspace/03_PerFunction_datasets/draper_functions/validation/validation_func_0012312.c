figure_label_len(const unsigned char *label, int len)
{
	const unsigned char *end = label + len - 1;

	while ((*end == ' ' || *end == 0) && end >= label)
		--end;
	if (end >= label) {
		label = label;
		return end - label + 1;
	}
	return 0;
}
