build_section_rename (const char *arg)
{
  struct rename_section_struct *r;
  char *this_arg = NULL;
  char *next_arg = NULL;

  for (this_arg = xstrdup (arg); this_arg != NULL; this_arg = next_arg)
    {
      char *old_name, *new_name;

      if (this_arg)
	{
	  next_arg = strchr (this_arg, ':');
	  if (next_arg)
	    {
	      *next_arg = '\0';
	      next_arg++;
	    }
	}

      old_name = this_arg;
      new_name = strchr (this_arg, '=');

      if (*old_name == '\0')
	{
	  as_warn (_("ignoring extra '-rename-section' delimiter ':'"));
	  continue;
	}
      if (!new_name || new_name[1] == '\0')
	{
	  as_warn (_("ignoring invalid '-rename-section' specification: '%s'"),
		   old_name);
	  continue;
	}
      *new_name = '\0';
      new_name++;


      for (r = section_rename; r != NULL; r = r->next)
	{
	  if (strcmp (r->old_name, old_name) == 0)
	    as_bad (_("section %s renamed multiple times"), old_name);
	  if (strcmp (r->new_name, new_name) == 0)
	    as_bad (_("multiple sections remapped to output section %s"),
		    new_name);
	}


      r = (struct rename_section_struct *)
	xmalloc (sizeof (struct rename_section_struct));
      r->old_name = xstrdup (old_name);
      r->new_name = xstrdup (new_name);
      r->next = section_rename;
      section_rename = r;
    }
}
