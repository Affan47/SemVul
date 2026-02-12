static int read_and_execute(bool interactive)
{
#if defined(__WIN__)
  String tmpbuf;
  String buffer;
#endif

  char	*line= NULL;
  char	in_string=0;
  ulong line_number=0;
  bool ml_comment= 0;
  COMMANDS *com;
  status.exit_status=1;

  for (;;)
  {
    if (!interactive)
    {
      line=batch_readline(status.line_buff);


      if (line && !line_number &&
           (uchar) line[0] == 0xEF &&
           (uchar) line[1] == 0xBB &&
           (uchar) line[2] == 0xBF)
        line+= 3;
      line_number++;
      if (!glob_buffer.length())
	status.query_start_line=line_number;
    }
    else
    {
      char *prompt= (char*) (ml_comment ? "   /*> " :
                             glob_buffer.is_empty() ?  construct_prompt() :
			     !in_string ? "    -> " :
			     in_string == '\'' ?
			     "    '> " : (in_string == '`' ?
			     "    `> " :
			     "    \"> "));
      if (opt_outfile && glob_buffer.is_empty())
	fflush(OUTFILE);

#if defined(__WIN__)
      tee_fputs(prompt, stdout);
      if (!tmpbuf.is_alloced())
        tmpbuf.alloc(65535);
      tmpbuf.length(0);
      buffer.length(0);
      size_t clen;
      do
      {
	line= my_cgets((char*)tmpbuf.ptr(), tmpbuf.alloced_length()-1, &clen);
        buffer.append(line, clen);


      } while (tmpbuf.alloced_length() <= clen);


      if (line)
        line= buffer.c_ptr();
#else
      if (opt_outfile)
	fputs(prompt, OUTFILE);


      if (line)
        free(line);
      line= readline(prompt);
#endif


      if (opt_outfile && line)
	fprintf(OUTFILE, "%s\n", line);
    }

    if (!line)
    {
      if (status.line_buff && status.line_buff->error)
        status.exit_status= 1;
      else
        status.exit_status= 0;
      break;
    }


    if ((named_cmds || glob_buffer.is_empty())
	&& !ml_comment && !in_string && (com=find_command(line,0)))
    {
      if ((*com->func)(&glob_buffer,line) > 0)
	break;
      if (glob_buffer.is_empty())
	in_string=0;
#ifdef HAVE_READLINE
      if (interactive && status.add_to_history && not_in_history(line))
	add_history(line);
#endif
      continue;
    }
    if (add_line(glob_buffer, line, &in_string, &ml_comment,
                 status.line_buff ? status.line_buff->truncated : 0))
      break;
  }


  if (!interactive && !status.exit_status)
  {
    remove_cntrl(glob_buffer);
    if (!glob_buffer.is_empty())
    {
      status.exit_status=1;
      if (com_go(&glob_buffer,line) <= 0)
	status.exit_status=0;
    }
  }

#if defined(__WIN__)
  buffer.free();
  tmpbuf.free();
#else
  if (interactive)


    free(line);
#endif


  return status.exit_status;
}
