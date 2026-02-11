StripWhiteSpace(const char* string)
{
    char *p, *new_string;
    int n;


    for (n=0, p=(char*)string; *p ; p++)
	if (!IsWhiteSpace(p))
	    n++;


    new_string = new char[n + 1];
    new_string[0] = '\0';

    for (n=0, p=(char*)string; *p ; p++) {
	if (!IsWhiteSpace(p)) {
	    new_string[n] = *p;
	    n++;
	}
    }
    new_string[n] = '\0';

    return new_string;
}
