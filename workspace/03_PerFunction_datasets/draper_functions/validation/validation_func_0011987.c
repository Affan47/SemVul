libmail_gpg_signencode(int dosign,
			   int doencode,


			   struct libmail_gpg_info *options)
{
	int rc;
	struct libmail_gpg_errhandler eh;

	eh.options=options;
	eh.err_flag=0;

	if (doencode != LIBMAIL_GPG_INDIVIDUAL &&
	    doencode != LIBMAIL_GPG_ENCAPSULATE)
		doencode=0;

	if (!dosign && !doencode)
	{
		(*options->errhandler_func)("Invalid arguments to"
					    " libmail_gpg_signencode",
					    options->errhandler_arg);
		return -1;
	}

	rc=dosignencode(dosign, doencode, 0,
			options->gnupghome,
			options->passphrase_fd,
			options->input_func,
			options->input_func_arg,
			options->output_func,
			options->output_func_arg,
			&libmail_gpg_errfunc,
			&eh,
			options->argc,
			options->argv,
			&options->errstatus);

	if (rc && !eh.err_flag)
		(*options->errhandler_func)(strerror(errno),
					    options->errhandler_arg);
	return rc;
}
