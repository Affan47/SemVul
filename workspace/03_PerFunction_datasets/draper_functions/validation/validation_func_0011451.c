ChopNL(string)
char *string;
{
    char c;
    char *ptr;

    c = '\0';

    for (ptr = string; *ptr; ptr++);

    if (ptr != string)
    {
	c = *(--ptr);

	if (c == '\n')
	{
	    *ptr = '\0';
	}
    }

    return (c);
}
