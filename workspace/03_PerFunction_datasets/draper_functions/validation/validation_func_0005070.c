chop(char *string)
{
    int i;
    int chopped;
    int stop = 0;

    chopped = 0;
    i = strlen(string) - 1;
    while (i >= 0) {
	stop = 1;
	if ((string[i] == '\n') || (string[i] == '\t') ||
	    (string[i] == ' ') || (string[i] == '\f') ||
	    (string[i] == '\r')) {
	    chopped++;
	    stop = 0;
	}
	if (stop == 1) {

	    break;
	}
	i--;
    }


    string[strlen(string) - chopped] = '\0';

    return (chopped);
}
