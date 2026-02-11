DXLIsHostLocal(const char *host)
{
    char localHostname[BUFSIZ];
    char localhostHostname[BUFSIZ];
    char remoteHostname[BUFSIZ];
    struct hostent *he;
    int  hostnameFound;
#if defined(HAVE_SIGPIPE)
    struct utsname Uts_Name;

    if (strcmp ("unix", host) == 0)
	return TRUE;

    he = gethostbyname ((char*)host);
    if (he == NULL) {
	fprintf(stderr, "%s: Invalid host", host);
	return(0);
    }
    strcpy(remoteHostname, he->h_name);

    if (uname(&Uts_Name) >= 0 && (he=gethostbyname(Uts_Name.nodename)) != NULL)
    {
	strcpy(localHostname, he->h_name);
	hostnameFound = 1;
    }
    else
    {
	hostnameFound = 0;
    }

    he = gethostbyname ("localhost");
    if (he == NULL) {
	fprintf(stderr, "%s: Invalid host", "localhost");
	return (0);
    }
    strcpy(localhostHostname, he->h_name);

    return ((hostnameFound && strcmp (localHostname, remoteHostname) == 0) ||
	    strcmp (localhostHostname, remoteHostname) == 0);
#else
    return TRUE;
#endif
}
