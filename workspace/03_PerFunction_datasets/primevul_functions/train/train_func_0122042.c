getAuthCookie(struct http_auth *hauth, char *auth_header,
	      TextList *extra_header, ParsedURL *pu, HRequest *hr,
	      FormList *request,
	      volatile Str *uname, volatile Str *pwd)
{
    Str ss = NULL;
    Str tmp;
    TextListItem *i;
    int a_found;
    int auth_header_len = strlen(auth_header);
    char *realm = NULL;
    int proxy;

    if (hauth)
	realm = qstr_unquote(get_auth_param(hauth->param, "realm"))->ptr;

    if (!realm)
	return;

    a_found = FALSE;
    for (i = extra_header->first; i != NULL; i = i->next) {
	if (!strncasecmp(i->ptr, auth_header, auth_header_len)) {
	    a_found = TRUE;
	    break;
	}
    }
    proxy = !strncasecmp("Proxy-Authorization:", auth_header,
			 auth_header_len);
    if (a_found) {


	if (fmInitialized) {
	    message("Wrong username or password", 0, 0);
	    refresh();
	}
	else
	    fprintf(stderr, "Wrong username or password\n");
	sleep(1);

	delText(extra_header, i);
	invalidate_auth_user_passwd(pu, realm, *uname, *pwd, proxy);
    }
    *uname = NULL;
    *pwd = NULL;

    if (!a_found && find_auth_user_passwd(pu, realm, (Str*)uname, (Str*)pwd,
					  proxy)) {
	 ;
    }
    else {
	if (QuietMessage)
	    return;

	sleep(2);
	if (fmInitialized) {
	    char *pp;
	    term_raw();

	    if ((pp = inputStr(Sprintf("Username for %s: ", realm)->ptr,
			       NULL)) == NULL)
		return;
	    *uname = Str_conv_to_system(Strnew_charp(pp));
	    if ((pp = inputLine(Sprintf("Password for %s: ", realm)->ptr, NULL,
				IN_PASSWORD)) == NULL) {
		*uname = NULL;
		return;
	    }
	    *pwd = Str_conv_to_system(Strnew_charp(pp));
	    term_cbreak();
	}
	else {


	    if (feof(stdin) || ferror(stdin)) {

		fprintf(stderr, "w3m: Authorization required for %s\n",
			realm);
		exit(1);
	    }


	    printf(proxy ? "Proxy Username for %s: " : "Username for %s: ",
		   realm);
	    fflush(stdout);
	    *uname = Strfgets(stdin);
	    Strchop(*uname);
#ifdef HAVE_GETPASSPHRASE
	    *pwd = Strnew_charp((char *)
				getpassphrase(proxy ? "Proxy Password: " :
					      "Password: "));
#else
#ifndef __MINGW32_VERSION
	    *pwd = Strnew_charp((char *)
				getpass(proxy ? "Proxy Password: " :
					"Password: "));
#else
	    term_raw();
	    *pwd = Strnew_charp((char *)
				inputLine(proxy ? "Proxy Password: " :
					  "Password: ", NULL, IN_PASSWORD));
	    term_cbreak();
#endif
#endif
	}
    }
    ss = hauth->cred(hauth, *uname, *pwd, pu, hr, request);
    if (ss) {
	tmp = Strnew_charp(auth_header);
	Strcat_m_charp(tmp, " ", ss->ptr, "\r\n", NULL);
	pushText(extra_header, tmp->ptr);
    }
    else {
	*uname = NULL;
	*pwd = NULL;
    }
    return;
}
