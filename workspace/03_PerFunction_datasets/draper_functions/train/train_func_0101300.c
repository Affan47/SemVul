initialize( ARGPARSE_ARGS *arg, const char *filename, unsigned *lineno )
{
  if( !(arg->flags & (1<<15)) )
    {

      arg->internal.idx = 0;
      arg->internal.last = NULL;
      arg->internal.inarg = 0;
      arg->internal.stopped = 0;
      arg->internal.aliases = NULL;
      arg->internal.cur_alias = NULL;
      arg->internal.iio_list = NULL;
      arg->err = 0;
      arg->flags |= 1<<15;
      if ( *arg->argc < 0 )
        jnlib_log_bug ("invalid argument for arg_parsee\n");
    }


  if (arg->err)
    {

      const char *s;

      if (filename)
        {
          if ( arg->r_opt == ARGPARSE_UNEXPECTED_ARG )
            s = _("argument not expected");
          else if ( arg->r_opt == ARGPARSE_READ_ERROR )
            s = _("read error");
          else if ( arg->r_opt == ARGPARSE_KEYWORD_TOO_LONG )
            s = _("keyword too long");
          else if ( arg->r_opt == ARGPARSE_MISSING_ARG )
            s = _("missing argument");
          else if ( arg->r_opt == ARGPARSE_INVALID_COMMAND )
            s = _("invalid command");
          else if ( arg->r_opt == ARGPARSE_INVALID_ALIAS )
            s = _("invalid alias definition");
          else if ( arg->r_opt == ARGPARSE_OUT_OF_CORE )
            s = _("out of core");
          else
            s = _("invalid option");
          jnlib_log_error ("%s:%u: %s\n", filename, *lineno, s);
	}
      else
        {
          s = arg->internal.last? arg->internal.last:"[??]";

          if ( arg->r_opt == ARGPARSE_MISSING_ARG )
            jnlib_log_error (_("missing argument for option \"%.50s\"\n"), s);
          else if ( arg->r_opt == ARGPARSE_UNEXPECTED_ARG )
            jnlib_log_error (_("option \"%.50s\" does not expect an "
                               "argument\n"), s );
          else if ( arg->r_opt == ARGPARSE_INVALID_COMMAND )
            jnlib_log_error (_("invalid command \"%.50s\"\n"), s);
          else if ( arg->r_opt == ARGPARSE_AMBIGUOUS_OPTION )
            jnlib_log_error (_("option \"%.50s\" is ambiguous\n"), s);
          else if ( arg->r_opt == ARGPARSE_AMBIGUOUS_OPTION )
            jnlib_log_error (_("command \"%.50s\" is ambiguous\n"),s );
          else if ( arg->r_opt == ARGPARSE_OUT_OF_CORE )
            jnlib_log_error ("%s\n", _("out of core\n"));
          else
            jnlib_log_error (_("invalid option \"%.50s\"\n"), s);
	}
      if ( arg->err != 1 )
        exit (2);
      arg->err = 0;
    }


  arg->r.ret_str = NULL;
  arg->r.ret_long = 0;
}
