wizard_read_defaults(void)
{
	gchar *rcpath;

	rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, "accountrc.tmpl", NULL);
	if (!is_file_exist(rcpath)) {
		str_write_to_file(accountrc_tmpl, rcpath);
	}

	prefs_read_config(template_params, "AccountTemplate", rcpath, NULL);

	PARSE_DEFAULT(tmpl.domain);
	PARSE_DEFAULT(tmpl.name);
	PARSE_DEFAULT(tmpl.email);
	PARSE_DEFAULT(tmpl.organization);
	PARSE_DEFAULT(tmpl.smtpserver);
	PARSE_DEFAULT(tmpl.smtpuser);
	PARSE_DEFAULT(tmpl.smtppass);
	PARSE_DEFAULT(tmpl.recvserver);
	PARSE_DEFAULT(tmpl.recvuser);
	PARSE_DEFAULT(tmpl.recvpass);
	PARSE_DEFAULT(tmpl.imapdir);
	PARSE_DEFAULT(tmpl.mboxfile);
	PARSE_DEFAULT(tmpl.mailbox);


	g_free(rcpath);
}
