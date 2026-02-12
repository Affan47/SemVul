static bool _pam_require_krb5_auth_after_chauthtok(struct pwb_context *ctx,
						   const char *user)
{


	char *new_authtok_reqd_during_auth = NULL;
	struct passwd *pwd = NULL;

	_pam_get_data(ctx->pamh, PAM_WINBIND_NEW_AUTHTOK_REQD_DURING_AUTH,
		      &new_authtok_reqd_during_auth);
	pam_set_data(ctx->pamh, PAM_WINBIND_NEW_AUTHTOK_REQD_DURING_AUTH,
		     NULL, NULL);

	if (new_authtok_reqd_during_auth) {
		return true;
	}

	pwd = getpwnam(user);
	if (!pwd) {
		return false;
	}

	if (getuid() == pwd->pw_uid) {
		return true;
	}

	return false;
}
