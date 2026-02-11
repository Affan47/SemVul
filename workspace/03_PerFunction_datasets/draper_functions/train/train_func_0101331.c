tty_update_title(string)
    char *string;
{
    if (tty_is_xterm(tty_type))
    {
	size_t len = strlen(string);
	char *temp = xmalloc(128 + len + 1);
	char *printable_string = xstrdup(string);

	toprintable(printable_string, len);
	sprintf(temp, "%c]2;%s - %s%c", 0x1b, PRODUCT, printable_string, 0x07);


	if (128 + (int)len > 2 * tty_columns)
	{
	    temp[2 * tty_columns    ] = 0x07;
	    temp[2 * tty_columns + 1] = '\0';
	}

	xwrite(TTY_OUTPUT, temp, strlen(temp));
	xfree(printable_string);
	xfree(temp);
	fflush(stdout);
    }
}
