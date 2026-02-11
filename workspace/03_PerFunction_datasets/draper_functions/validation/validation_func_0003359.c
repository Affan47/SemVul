add_string_str_html(const char *s, int maxlen)
{
	int l = 0;
	char *str = xmalloc(6 * strlen(s) + 1);
	char *cptr = str;
	for(; *s; s++)
	{
		if(maxlen && l > abs(maxlen))
		{
			cptr += sprintf(cptr, "...");
			break;
		}
		if(*s < 0x20)
		{
			if(*s == '\n')
			{
				if(maxlen < 0)
					*cptr++ = ' ';
				else
					cptr += sprintf(cptr, "<br%s>", conf.html_level == HTMLLEVEL_X ? " /" : "");
			}
		}
		else if(*s >= 0x7f || *s == '"')
			cptr += sprintf(cptr, "&#%d;", (int)(unsigned char)*s);
		else if(*s == '<')
			cptr += sprintf(cptr, "&lt;");
		else if(*s == '>')
			cptr += sprintf(cptr, "&gt;");
		else if(*s == '&')
			cptr += sprintf(cptr, "&amp;");
		else if(*s == '"')
			cptr += sprintf(cptr, "&quot;");
		else
			*cptr++ = *s;
		l++;
	}
	*cptr = '\0';
	add_string_str(str);
	xfree(str);
}
