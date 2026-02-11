postfixcmp(const char *string, const char *postfix)
{
	int len1 = strlen(string), len2 = strlen(postfix);
	if (len1 < len2)
		return 1;
	return strcmp(string + len1 - len2, postfix);
}
