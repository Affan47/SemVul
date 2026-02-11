scanopt_err (s, opt_offset, is_short, err)
     struct _scanopt_t *s;
     int     opt_offset;
     int     is_short;
     int     err;
{
	const char *optname = "";
	char    optchar[2];
	const optspec_t *opt = NULL;

	if (opt_offset >= 0)
		opt = s->options + opt_offset;

	if (!s->no_err_msg) {

		if (s->index > 0 && s->index < s->argc) {
			if (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			else {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		switch (err) {
		case SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			break;
		case SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			break;
		case SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			break;
		case SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			break;
		default:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			break;
		}
	}
	return err;
}
