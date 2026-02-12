static int pam_winbind_request_log(struct pwb_context *ctx,
				   int retval,
				   const char *user,
				   const char *fn)
{
	switch (retval) {
	case PAM_AUTH_ERR:

		_pam_log(ctx, LOG_WARNING, "user '%s' denied access "
			 "(incorrect password or invalid membership)", user);
		return retval;
	case PAM_ACCT_EXPIRED:

		_pam_log(ctx, LOG_WARNING, "user '%s' account expired",
			 user);
		return retval;
	case PAM_AUTHTOK_EXPIRED:

		_pam_log(ctx, LOG_WARNING, "user '%s' password expired",
			 user);
		return retval;
	case PAM_NEW_AUTHTOK_REQD:

		_pam_log(ctx, LOG_WARNING, "user '%s' new password "
			 "required", user);
		return retval;
	case PAM_USER_UNKNOWN:

		_pam_log_debug(ctx, LOG_NOTICE, "user '%s' not found",
			       user);
		if (ctx->ctrl & WINBIND_UNKNOWN_OK_ARG) {
			return PAM_IGNORE;
		}
		return retval;
	case PAM_SUCCESS:

		if (strcmp(fn, "wbcLogonUser") == 0) {
			_pam_log(ctx, LOG_NOTICE,
				 "user '%s' granted access", user);
		} else {
			_pam_log(ctx, LOG_NOTICE,
				 "user '%s' OK", user);
		}
		return retval;
	default:

		_pam_log(ctx, LOG_ERR,
			 "internal module error (retval = %s(%d), user = '%s')",
			_pam_error_code_str(retval), retval, user);
		return retval;
	}
}
