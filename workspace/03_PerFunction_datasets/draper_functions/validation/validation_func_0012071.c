query_afilias(const int sock, const char *query)
{
    char *temp, *p, buf[2000];
    FILE *fi;
    int hide = hide_discl;
    char *referral_server = NULL;
    int state = 0;

    temp = malloc(strlen(query) + 2 + 1);
    strcpy(temp, query);
    strcat(temp, "\r\n");

    fi = fdopen(sock, "r");
    if (write(sock, temp, strlen(temp)) < 0)
	err_sys("write");
    free(temp);

    while (fgets(buf, sizeof(buf), fi)) {
	if (state == 0 && strneq(buf, "Domain Name:", 12))
	    state = 1;
	if (state == 1 && strneq(buf, "Whois Server:", 13)) {
	    for (p = buf; *p != ':'; p++);
	    for (p++; *p == ' '; p++);
	    referral_server = strdup(p);
	    if ((p = strpbrk(referral_server, "\r\n ")))
		*p = '\0';
	}

	if (hide_line(&hide, buf))
	    continue;

	if ((p = strpbrk(buf, "\r\n")))
	    *p = '\0';
	recode_fputs(buf, stdout);
	fputc('\n', stdout);
    }

    if (ferror(fi))
	err_sys("fgets");
    fclose(fi);

    if (hide > HIDE_NOT_STARTED)
	err_quit(_("Catastrophic error: disclaimer text has been changed.\n"
		   "Please upgrade this program.\n"));

    return referral_server;
}
