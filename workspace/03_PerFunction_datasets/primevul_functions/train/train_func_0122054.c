checkRedirection(ParsedURL *pu)
{
    static ParsedURL *puv = NULL;
    static int nredir = 0;
    static int nredir_size = 0;
    Str tmp;

    if (pu == NULL) {
	nredir = 0;
	nredir_size = 0;
	puv = NULL;
	return TRUE;
    }
    if (nredir >= FollowRedirection) {

	tmp = Sprintf("Number of redirections exceeded %d at %s",
		      FollowRedirection, parsedURL2Str(pu)->ptr);
	disp_err_message(tmp->ptr, FALSE);
	return FALSE;
    }
    else if (nredir_size > 0 &&
	     (same_url_p(pu, &puv[(nredir - 1) % nredir_size]) ||
	      (!(nredir % 2)
	       && same_url_p(pu, &puv[(nredir / 2) % nredir_size])))) {

	tmp = Sprintf("Redirection loop detected (%s)",
		      parsedURL2Str(pu)->ptr);
	disp_err_message(tmp->ptr, FALSE);
	return FALSE;
    }
    if (!puv) {
	nredir_size = FollowRedirection / 2 + 1;
	puv = New_N(ParsedURL, nredir_size);
	memset(puv, 0, sizeof(ParsedURL) * nredir_size);
    }
    copyParsedURL(&puv[nredir % nredir_size], pu);
    nredir++;
    return TRUE;
}
