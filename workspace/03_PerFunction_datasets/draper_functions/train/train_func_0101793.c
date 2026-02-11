handle_redirect (char *args, size_t len)
{
    static List *redirects = NULL;

    TRACE (TRACE_FUNCTION, "handle_redirect (%s)", args);

    if (redirects && findnode (redirects, args))
	error (1, 0, "`Redirect' loop detected.  Server misconfiguration?");
    else
    {
	if (!redirects) redirects = getlist();
	push_string (redirects, args);
    }

    if (referred_since_last_redirect)
	referred_since_last_redirect = false;
    else
    {
	if (free_client_referrer) free (client_referrer);
	client_referrer = current_parsed_root;
	free_client_referrer = false;
    }

    current_parsed_root = parse_cvsroot (args);


    if (!current_parsed_root)
	error (1, 0, "Server requested redirect to invalid root: `%s'",
	       args);
}
