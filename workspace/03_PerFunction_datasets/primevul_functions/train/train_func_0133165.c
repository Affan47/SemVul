Pluralise(string)
    register char *string;
{
    register int length;
    static char area[STRINGSIZE];
    length = strlen(string);
    strcpy(area, string);

    if (!Suffix(string, "ch") ||
	!Suffix(string, "ex") ||
	!Suffix(string, "ix") ||
	!Suffix(string, "sh") ||
	!Suffix(string, "ss"))
    {

	strcat(area, "es");
    } else if (length > 2 && string[length - 1] == 'y')
    {
	if (strchr("aeiou", string[length - 2]))
	{

	    strcat(area, "s");
	} else
	{

	    strcpy(area + length - 1, "ies");
	}
    } else if (string[length - 1] == 's')
    {

	strcat(area, "es");
    } else
    {

	strcat(area, "s");
    }

    return (area);
}
