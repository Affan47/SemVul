add_printer_filter(
    const char  *command,
    mime_t      *mime,
    mime_type_t *filtertype,
    const char  *filter)
{
  char		super[MIME_MAX_SUPER],
		type[MIME_MAX_TYPE],
		dsuper[MIME_MAX_SUPER],
		dtype[MIME_MAX_TYPE],
		dest[MIME_MAX_SUPER + MIME_MAX_TYPE + 2],

		program[1024];
  int		cost;
  size_t	maxsize = 0;
  mime_type_t	*temptype,
		*desttype;
  mime_filter_t	*filterptr;


  if (sscanf(filter, "%15[^/]/%255s%*[ \t]%15[^/]/%255s%d%*[ \t]%1023[^\n]",
             super, type, dsuper, dtype, &cost, program) == 6)
  {
    snprintf(dest, sizeof(dest), "%s/%s/%s", filtertype->type, dsuper, dtype);

    if ((desttype = mimeType(mime, "printer", dest)) == NULL)
      desttype = mimeAddType(mime, "printer", dest);
  }
  else
  {
    if (sscanf(filter, "%15[^/]/%255s%d%*[ \t]%1023[^\n]", super, type, &cost,
               program) == 4)
    {
      desttype = filtertype;
    }
    else
    {
      _cupsLangPrintf(stderr, _("%s: Invalid filter string \"%s\"."), command,
		      filter);
      return;
    }
  }

  if (!strncmp(program, "maxsize(", 8))
  {
    char	*ptr;

    maxsize = strtoll(program + 8, &ptr, 10);

    if (*ptr != ')')
    {
      printf("testmime: Invalid filter string \"%s\".\n", filter);
      return;
    }

    ptr ++;
    while (_cups_isspace(*ptr))
      ptr ++;

    _cups_strcpy(program, ptr);
  }


  if (strcmp(program, "-"))
  {
    char filename[1024];

    if (program[0] == '/')
      strlcpy(filename, program, sizeof(filename));
    else
      snprintf(filename, sizeof(filename), "%s/filter/%s", ServerBin, program);

    if (_cupsFileCheck(filename, _CUPS_FILE_CHECK_PROGRAM, !geteuid(), check_cb,
                       (void *)command))
      return;
  }


  for (temptype = mimeFirstType(mime);
       temptype;
       temptype = mimeNextType(mime))
    if (((super[0] == '*' && _cups_strcasecmp(temptype->super, "printer")) ||
         !_cups_strcasecmp(temptype->super, super)) &&
        (type[0] == '*' || !_cups_strcasecmp(temptype->type, type)))
    {
      if (desttype != filtertype)
      {
        filterptr = mimeAddFilter(mime, temptype, desttype, cost, program);

        if (!mimeFilterLookup(mime, desttype, filtertype))
          mimeAddFilter(mime, desttype, filtertype, 0, "-");
      }
      else
        filterptr = mimeAddFilter(mime, temptype, filtertype, cost, program);

      if (filterptr)
	filterptr->maxsize = maxsize;
    }
}
