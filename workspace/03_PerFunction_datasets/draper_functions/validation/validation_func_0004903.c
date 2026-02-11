parseAtPort(const char* url, PRInt32 *port, char **path)
{
	PRStatus status = PR_SUCCESS;
    static const char delimiters[] = "/?#";
    char* brk = PL_strpbrk(url, delimiters);
    if (!brk)
    {
        *port = getPort(url);
        if (*port <= 0) {

            return PR_FAILURE;
		} else {
            return status;
		}
    }

    switch (*brk)
    {
		case '/' :
		case '?' :
		case '#' :

			*port = getPort(url);
			if (*port <= 0) {

				return PR_FAILURE;
			}
			status = parseAtPath(brk, path);
			break;
		default:

			break;
	}
    return status;
}
