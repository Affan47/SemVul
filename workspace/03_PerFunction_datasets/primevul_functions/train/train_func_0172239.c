main_set_appheader (xd3_stream *stream, main_file *input, main_file *sfile)
{


  if (appheader_used || ! option_use_appheader) { return 0; }


  if (option_appheader)
    {
      appheader_used = option_appheader;
    }
  else
    {
      const char *iname;
      const char *icomp;
      const char *sname;
      const char *scomp;
      usize_t len;

      iname = main_apphead_string (input->filename);
      icomp = (input->compressor == NULL) ? "" : input->compressor->ident;
      len = (usize_t) strlen (iname) + (usize_t) strlen (icomp) + 2;

      if (sfile->filename != NULL)
	{
	  sname = main_apphead_string (sfile->filename);
	  scomp = (sfile->compressor == NULL) ? "" : sfile->compressor->ident;
	  len += (usize_t) strlen (sname) + (usize_t) strlen (scomp) + 2;
	}
      else
	{
	  sname = scomp = "";
	}

      if ((appheader_used = (uint8_t*) main_malloc (len)) == NULL)
	{
	  return ENOMEM;
	}

      if (sfile->filename == NULL)
	{
	  snprintf_func ((char*)appheader_used, len, "%s/%s", iname, icomp);
	}
      else
	{
	  snprintf_func ((char*)appheader_used, len, "%s/%s/%s/%s",
		    iname, icomp, sname, scomp);
	}
    }

  xd3_set_appheader (stream, appheader_used,
		     (usize_t) strlen ((char*)appheader_used));

  return 0;
}
