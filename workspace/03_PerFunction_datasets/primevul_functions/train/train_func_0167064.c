fetchname (char const *at, int strip_leading, bool maybe_quoted, char **pname,
	   char **ptimestr, struct timespec *pstamp)
{
    char *name;
    const char *t;
    char *timestr = NULL;
    struct timespec stamp;

    stamp.tv_sec = -1;

    while (ISSPACE ((unsigned char) *at))
	at++;
    if (debug & 128)
	say ("fetchname %s %d\n", at, strip_leading);

    if (maybe_quoted && *at == '"')
      {
	name = parse_c_string (at, &t);
	if (! name)
	  {
	    if (debug & 128)
	      say ("ignoring malformed filename %s\n", quotearg (at));
	    return;
	  }
      }
    else
      {
	for (t = at;  *t;  t++)
	  {
	    if (ISSPACE ((unsigned char) *t))
	      {


		char const *u = t;
		while (*u != '\t' && ISSPACE ((unsigned char) u[1]))
		  u++;
		if (*u != '\t' && (strchr (u + 1, pstamp ? '\t' : '\n')))
		  continue;
		break;
	      }
	  }
	name = savebuf (at, t - at + 1);
	name[t - at] = 0;
      }


    if (strcmp (name, "/dev/null") == 0)
      {
	free (name);
	if (pstamp)
	  {
	    pstamp->tv_sec = 0;
	    pstamp->tv_nsec = 0;
	  }
	return;
      }


    if (! strip_leading_slashes (name, strip_leading))
      {
	free (name);
	return;
      }

    if (ptimestr)
      {
	char const *u = t + strlen (t);

	if (u != t && *(u-1) == '\n')
	  u--;
	if (u != t && *(u-1) == '\r')
	  u--;
	timestr = savebuf (t, u - t + 1);
	timestr[u - t] = 0;
      }

      if (*t == '\n')
	stamp.tv_sec = -1;
      else
	{
	  if (! pstamp)
	    {
	      free (name);
	      return;
	    }

	  if (set_time | set_utc)
	    get_date (&stamp, t, &initial_time);
	  else
	    {


	      const struct timespec lower = { -25L * 60 * 60 },
				    upper = {  26L * 60 * 60 };
	      if (get_date (&stamp, t, &initial_time)
		  && timespec_cmp (stamp, lower) > 0
		  && timespec_cmp (stamp, upper) < 0) {
		      stamp.tv_sec = 0;
		      stamp.tv_nsec = 0;
	      }
	    }
	}

    free (*pname);
    *pname = name;
    if (ptimestr)
      {
	free (*ptimestr);
	*ptimestr = timestr;
      }
    if (pstamp)
      *pstamp = stamp;
}
