static int check_entry_match(const char *a, int a_len, const char *b, int b_len)
{


	int cmp = name_compare(a, a_len, b, b_len);


	if (!cmp)
		return cmp;

	if (0 < cmp) {


		return 1;
	}


	if (a_len < b_len && !memcmp(a, b, a_len) && b[a_len] < '/')
		return 1;

	return -1;
}
