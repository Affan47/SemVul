get_one_responsible_addr (const DatabaseInfo database,
			  int full, int strict, const char *name)
{
  AdmEntry *r;
  char *p;
  char *address = NULL;


  if (strpbrk (name, "<(@") != NULL)
    {
      return xstrdup (name);
    }


  p = (char *) strchr (name, ' ');
  if (p != (char *) NULL)
    {
      *p = '\0';
    }
  p = (char *) strchr (name, '(');
  if (p != (char *) NULL)
    {
      *p = '\0';
    }

  r = get_responsible_address (database, name);

  if (r != NULL && ((! strict)
		    || r->admFields[ResponsibleAdmFullname][0] != '\0'))
    {
      if (full)
	{
	  asprintf (&address, "%s:%s:%s", r->admFields[ResponsibleAdmKey],
		    r->admFields[ResponsibleAdmFullname],
		    r->admFields[ResponsibleAdmAlias]);
	}
      else
	{


	  char *addr = r->admFields[ResponsibleAdmAlias];

	  while (*addr != '\0' && ! isalpha ((int) *addr))
	    {
	      addr++;
	    }
	  if (*addr != '\0')
	    {
	      address = xstrdup (addr);
	    }
	  else
	    {
	      address = xstrdup (r->admFields[ResponsibleAdmKey]);
	    }
	}
    }
  free_adm_entry (r);

  return address;
}
