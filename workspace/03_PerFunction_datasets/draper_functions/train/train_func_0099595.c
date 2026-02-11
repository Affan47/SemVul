output_escaped_str(char *str)
{
	int			i,
				len = strlen(str);


	for (i = 0; i < len; i++)
	{
		if (str[i] == '"')
			fputs("\\\"", yyout);
		else if (str[i] == '\n')
			fputs("\\\n", yyout);
		else if (str[i] == '\r' && str[i + 1] == '\n')
		{
			fputs("\\\r\n", yyout);
			i++;
		}
		else
			fputc(str[i], yyout);
	}
}
