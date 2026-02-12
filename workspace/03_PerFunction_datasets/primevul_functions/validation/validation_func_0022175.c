static int isAnonGraph(char *name)
{
    if (*name++ != '%')
	return 0;
    while (isdigit(*name))
	name++;
    return (*name == '\0');
}
