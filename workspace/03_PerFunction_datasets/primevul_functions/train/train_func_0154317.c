_parse_config_file(pam_handle_t *pamh, int ctrl, const char *file)
{
    int retval;
    char buffer[BUF_SIZE];
    FILE *conf;
    VAR Var, *var=&Var;

    D(("Called."));

    var->name=NULL; var->defval=NULL; var->override=NULL;

    D(("Config file name is: %s", file));


    if ((conf = fopen(file,"r")) == NULL) {
      pam_syslog(pamh, LOG_ERR, "Unable to open config file: %s: %m", file);
      return PAM_IGNORE;
    }


    while (( retval = _assemble_line(conf, buffer, BUF_SIZE)) > 0) {
      D(("Read line: %s", buffer));

      if ((retval = _parse_line(pamh, buffer, var)) == GOOD_LINE) {
	retval = _check_var(pamh, var);

	if (DEFINE_VAR == retval) {
	  retval = _define_var(pamh, ctrl, var);

	} else if (UNDEFINE_VAR == retval) {
	  retval = _undefine_var(pamh, ctrl, var);
	}
      }
      if (PAM_SUCCESS != retval && ILLEGAL_VAR != retval
	  && BAD_LINE != retval && PAM_BAD_ITEM != retval) break;

      _clean_var(var);

    }

    (void) fclose(conf);


    _clean_var(var);

    D(("Exit."));
    return (retval != 0 ? PAM_ABORT : PAM_SUCCESS);
}
