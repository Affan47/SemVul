tag_is_valid(char *tag_string)
{
	if (!g_ascii_strncasecmp(tag_string, "head", 4)
		|| !g_ascii_strncasecmp(tag_string, "hr", 2)
		|| !g_ascii_strncasecmp(tag_string, "br", 2)
		|| !g_ascii_strncasecmp(tag_string, "body", 4)
		|| !g_ascii_strcasecmp(tag_string, "p")
		|| !g_ascii_strcasecmp(tag_string, "html")
		|| !g_ascii_strcasecmp(tag_string, "title")
		|| !g_ascii_strcasecmp(tag_string, "pre")
		|| !g_ascii_strcasecmp(tag_string, "b")
		|| !g_ascii_strcasecmp(tag_string, "u")
		|| !g_ascii_strcasecmp(tag_string, "i")
		|| !g_ascii_strncasecmp(tag_string, "font", 4)
		|| !g_ascii_strncasecmp(tag_string, "a ", 2)
		|| !g_ascii_strcasecmp(tag_string, "a")
		|| !g_ascii_strncasecmp(tag_string, "smiley", 6)
		|| !g_ascii_strncasecmp(tag_string, "img", 3)) {
		return TRUE;
	}

	return FALSE;
}
