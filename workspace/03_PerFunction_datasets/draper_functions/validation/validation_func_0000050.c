trim_leading_whitespace(char *str)
{
	size_t i, len;
	for (i = 0; str[i] != '\0' && isspace(str[i]); i++) ;
	len = strlen(str + i);
	memmove(str, str + i, len + 1);
}
