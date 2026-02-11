serve_directory (char *arg)
{
    int status;
    char *repos;

    TRACE (TRACE_FUNCTION, "serve_directory (%s)", arg ? arg : "(null)");


    status = buf_read_line (buf_from_net, &repos, NULL);
    if (status == 0)
    {
	if (!ISABSOLUTE (repos))
	{


	    char *short_repos;

	    short_repos = repos;
	    repos = Xasprintf ("%s/%s",
	                      current_parsed_root->directory, short_repos);
	    free (short_repos);
	}
	else
	    repos = xstrdup (primary_root_translate (repos));

	if (
# ifdef PROXY_SUPPORT
	    !proxy_log &&
# endif
	    !outside_root (repos))
	    dirswitch (arg, repos);
	free (repos);
    }
    else if (status == -2)
    {
	pending_error = ENOMEM;
    }
    else if (status != 0)
    {
	pending_error_text = xmalloc (80 + strlen (arg));
	if (pending_error_text == NULL)
	{
	    pending_error = ENOMEM;
	}
	else if (status == -1)
	{
	    sprintf (pending_error_text,
		     "E end of file reading mode for %s", arg);
	}
	else
	{
	    sprintf (pending_error_text,
		     "E error reading mode for %s", arg);
	    pending_error = status;
	}
    }
}
