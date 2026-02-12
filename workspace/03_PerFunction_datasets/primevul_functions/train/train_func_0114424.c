parse_params(pam_handle_t *pamh, int argc, const char **argv, struct pam_params *p) {

  for (; argc-- > 0; ++argv) {
    const char *str;
    char *ep = NULL;
    if ((str = pam_str_skip_prefix(*argv, "startuid=")) != NULL) {
      p->start_uid = str_to_uid(pamh, str, p->start_uid, "startuid");
    } else if ((str = pam_str_skip_prefix(*argv, "enduid=")) != NULL) {
      p->end_uid = str_to_uid(pamh, str, p->end_uid, "enduid");
    } else if ((str = pam_str_skip_prefix(*argv, "fs=")) != NULL) {
      p->fs = str;
      p->fs_len = strlen(str);

      if (p->fs_len > 1 && p->fs[p->fs_len - 1] == '/')
        --p->fs_len;
    } else if ((str = pam_str_skip_prefix(*argv, "overwrite=")) != NULL) {
      errno = 0;
      p->overwrite = strtol(str, &ep, 10);
      if (*ep != '\0' || str == ep || errno !=0 || (p->overwrite < 0)) {
        pam_syslog(pamh, LOG_ERR, "Parameter \"overwrite=%s\" invalid, "
                        "setting to 0", str);
        p->overwrite = 0;
      }
    } else if ((str = pam_str_skip_prefix(*argv, "debug=")) != NULL) {
      errno = 0;
      p->debug = strtol(str, &ep, 10);
      if (*ep != '\0' || str == ep || errno != 0 || (p->debug < 0)) {
        pam_syslog(pamh, LOG_ERR, "Parameter \"debug=%s\" invalid, "
                        "setting to 0", str);
        p->debug = 0;
      }
    }
  }
}
