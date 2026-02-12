authorize_user_token (struct cfg *cfg,
		      const char *username,
		      const char *otp_id)
{
  int retval;

  if (cfg->auth_file)
    {


      retval = check_user_token (cfg, cfg->auth_file, username, otp_id);
    }
  else
    {
      char *userfile = NULL;


      if (! get_user_cfgfile_path (NULL, "authorized_yubikeys", username, &userfile))
	return 0;

      retval = check_user_token (cfg, userfile, username, otp_id);

      free (userfile);
    }

  return retval;
#undef USERFILE
}
