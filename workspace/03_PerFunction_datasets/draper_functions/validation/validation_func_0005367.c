scm_make_srcprops (long line, int col, SCM filename, SCM copy, SCM plist)
{
  if (!SCM_UNBNDP (filename))
    {
      SCM old_plist = plist;


      SCM last_acons = SCM_CDR (scm_last_plist_filename);
      if (old_plist == SCM_EOL
	  && SCM_CDAR (last_acons) == filename)
	{
	  plist = last_acons;
	}
      else
	{
	  plist = scm_acons (scm_sym_filename, filename, plist);
	  if (old_plist == SCM_EOL)
	    SCM_SETCDR (scm_last_plist_filename, plist);
	}
    }

  SCM_RETURN_NEWSMOB3 (scm_tc16_srcprops,
		       SRCPROPMAKPOS (line, col),
		       copy,
		       plist);
}
