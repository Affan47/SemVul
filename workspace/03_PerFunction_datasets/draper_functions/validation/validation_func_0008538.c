is_separator(char c)
{
	if (isspace(c))
		return 1;
	return parser_separators && c && strchr(parser_separators, c);
}
