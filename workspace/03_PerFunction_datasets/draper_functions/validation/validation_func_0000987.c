end_string (	char	*string,
		char	c,
		FILE	*file )
{
	return ((string[0] == c) && file_string_appear(file, &(string[1])));
}
