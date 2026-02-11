setipxname (int slot,char **argv)
{
    char *dest = ipxcp_wantoptions[slot].name;
    char *src  = *argv;
    int  count;
    char ch;

    ipxcp_wantoptions[slot].neg_name  = 1;
    ipxcp_allowoptions[slot].neg_name = 1;
    memset (dest, '\0', sizeof (ipxcp_wantoptions[slot].name));

    count = 0;
    while (*src) {
        ch = *src++;
	if (! isalnum (ch) && ch != '_') {
	    fprintf (stderr,
		     "%s: IPX router name must be alphanumeric or _\n",
		     progname);
	    return 0;
	}

	if (count >= sizeof (ipxcp_wantoptions[slot].name)) {
	    fprintf (stderr,
		     "%s: IPX router name is limited to %d characters\n",
		     progname,
		     (int) sizeof (ipxcp_wantoptions[slot].name) - 1);
	    return 0;
	}

	dest[count++] = toupper (ch);
    }

    return 1;
}
