pam_sm_acct_mgmt(pam_handle_t *pamh, int flags UNUSED,
		 int argc, const char **argv)
{
    const char *username;
    const char *database = NULL;
    const char *cryptmode = NULL;
    int retval = PAM_AUTH_ERR, ctrl;


    ctrl = _pam_parse(pamh, argc, argv, &database, &cryptmode);


    retval = pam_get_user(pamh, &username, NULL);
    if ((retval != PAM_SUCCESS) || (!username)) {
        pam_syslog(pamh, LOG_ERR,"can not get the username");
        return PAM_SERVICE_ERR;
    }


    retval = user_lookup(pamh, database, cryptmode, username, "", ctrl);
    switch (retval) {
        case -2:

	    return PAM_SERVICE_ERR;
	case -1:


	case 0:

	    return PAM_SUCCESS;
	case 1:

	    return PAM_USER_UNKNOWN;
        default:

	    pam_syslog(pamh, LOG_ERR,
		       "internal module error (retval = %d, user = `%s'",
		       retval, username);
            return PAM_SERVICE_ERR;
    }

    return PAM_SUCCESS;
}
