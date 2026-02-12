int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags,
		   int argc, const char **argv)
{
	const char *username;
	int ret = PAM_USER_UNKNOWN;
	const char *tmp = NULL;
	struct pwb_context *ctx = NULL;

	ret = _pam_winbind_init_context(pamh, flags, argc, argv, &ctx);
	if (ret) {
		goto out;
	}

	_PAM_LOG_FUNCTION_ENTER("pam_sm_acct_mgmt", ctx);


	ret = pam_get_user(pamh, &username, NULL);
	if ((ret != PAM_SUCCESS) || (!username)) {
		_pam_log_debug(ctx, LOG_DEBUG,
			       "can not get the username");
		ret = PAM_SERVICE_ERR;
		goto out;
	}


	ret = valid_user(ctx, username);
	switch (ret) {
	case -1:

		ret = PAM_SERVICE_ERR;
		goto out;
	case 1:

		_pam_log_debug(ctx, LOG_NOTICE, "user '%s' not found",
			       username);
		if (ctx->ctrl & WINBIND_UNKNOWN_OK_ARG) {
			ret = PAM_IGNORE;
			goto out;
		}
		ret = PAM_USER_UNKNOWN;
		goto out;
	case 0:
		pam_get_data(pamh, PAM_WINBIND_NEW_AUTHTOK_REQD,
			     (const void **)&tmp);
		if (tmp != NULL) {
			ret = atoi(tmp);
			switch (ret) {
			case PAM_AUTHTOK_EXPIRED:

			case PAM_NEW_AUTHTOK_REQD:
				_pam_log(ctx, LOG_WARNING,
					 "pam_sm_acct_mgmt success but %s is set",
					 PAM_WINBIND_NEW_AUTHTOK_REQD);
				_pam_log(ctx, LOG_NOTICE,
					 "user '%s' needs new password",
					 username);

				ret = PAM_NEW_AUTHTOK_REQD;
				goto out;
			default:
				_pam_log(ctx, LOG_WARNING,
					 "pam_sm_acct_mgmt success");
				_pam_log(ctx, LOG_NOTICE,
					 "user '%s' granted access", username);
				ret = PAM_SUCCESS;
				goto out;
			}
		}


		_pam_log(ctx, LOG_NOTICE,
			 "user '%s' granted access", username);
		ret = PAM_SUCCESS;
		goto out;
	default:

		_pam_log(ctx, LOG_ERR,
			 "internal module error (ret = %d, user = '%s')",
			 ret, username);
		ret = PAM_SERVICE_ERR;
		goto out;
	}


	ret = PAM_IGNORE;

 out:

	_PAM_LOG_FUNCTION_LEAVE("pam_sm_acct_mgmt", ctx, ret);

	TALLOC_FREE(ctx);

	return ret;
}
