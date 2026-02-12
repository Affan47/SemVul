int pam_sm_chauthtok(pam_handle_t * pamh, int flags,
		     int argc, const char **argv)
{
	unsigned int lctrl;
	int ret;
	bool cached_login = false;


	const char *user;
	char *pass_old, *pass_new;


	char *Announce;

	int retry = 0;
	char *username_ret = NULL;
	struct wbcAuthErrorInfo *error = NULL;
	struct pwb_context *ctx = NULL;

	ret = _pam_winbind_init_context(pamh, flags, argc, argv, &ctx);
	if (ret) {
		goto out;
	}

	_PAM_LOG_FUNCTION_ENTER("pam_sm_chauthtok", ctx);

	cached_login = (ctx->ctrl & WINBIND_CACHED_LOGIN);


	ctx->ctrl &= ~WINBIND_CACHED_LOGIN;


	ret = pam_get_user(pamh, &user, _("Username: "));
	if (ret) {
		_pam_log(ctx, LOG_ERR,
			 "password - could not identify user");
		goto out;
	}

	if (user == NULL) {
		_pam_log(ctx, LOG_ERR, "username was NULL!");
		ret = PAM_USER_UNKNOWN;
		goto out;
	}

	_pam_log_debug(ctx, LOG_DEBUG, "username [%s] obtained", user);


	ret = valid_user(ctx, user);
	switch (ret) {
		case 1:
			ret = PAM_USER_UNKNOWN;
			goto out;
		case -1:
			ret = PAM_SYSTEM_ERR;
			goto out;
		default:
			break;
	}


	if (flags & PAM_PRELIM_CHECK) {
		time_t pwdlastset_prelim = 0;


#define greeting _("Changing password for")
		Announce = talloc_asprintf(ctx, "%s %s", greeting, user);
		if (!Announce) {
			_pam_log(ctx, LOG_CRIT,
				 "password - out of memory");
			ret = PAM_BUF_ERR;
			goto out;
		}
#undef greeting

		lctrl = ctx->ctrl | WINBIND__OLD_PASSWORD;
		ret = _winbind_read_password(ctx, lctrl,
						Announce,
						_("(current) NT password: "),
						NULL,
						(const char **) &pass_old);
		TALLOC_FREE(Announce);
		if (ret != PAM_SUCCESS) {
			_pam_log(ctx, LOG_NOTICE,
				 "password - (old) token not obtained");
			goto out;
		}


		ret = winbind_auth_request(ctx, user, pass_old,
					   NULL, NULL, 0,
					   &error, NULL, NULL,
					   &pwdlastset_prelim, NULL);

		if (ret != PAM_ACCT_EXPIRED &&
		    ret != PAM_AUTHTOK_EXPIRED &&
		    ret != PAM_NEW_AUTHTOK_REQD &&
		    ret != PAM_SUCCESS) {
			pass_old = NULL;
			goto out;
		}

		pam_set_data(pamh, PAM_WINBIND_PWD_LAST_SET,
			     (void *)pwdlastset_prelim, NULL);

		ret = pam_set_item(pamh, PAM_OLDAUTHTOK,
				   (const void *) pass_old);
		pass_old = NULL;
		if (ret != PAM_SUCCESS) {
			_pam_log(ctx, LOG_CRIT,
				 "failed to set PAM_OLDAUTHTOK");
		}
	} else if (flags & PAM_UPDATE_AUTHTOK) {

		time_t pwdlastset_update = 0;


		ret = _pam_get_item(pamh, PAM_OLDAUTHTOK, &pass_old);

		if (ret != PAM_SUCCESS) {
			_pam_log(ctx, LOG_NOTICE,
				 "user not authenticated");
			goto out;
		}

		lctrl = ctx->ctrl & ~WINBIND_TRY_FIRST_PASS_ARG;

		if (on(WINBIND_USE_AUTHTOK_ARG, lctrl)) {
			lctrl |= WINBIND_USE_FIRST_PASS_ARG;
		}
		retry = 0;
		ret = PAM_AUTHTOK_ERR;
		while ((ret != PAM_SUCCESS) && (retry++ < MAX_PASSWD_TRIES)) {


			ret = _winbind_read_password(ctx, lctrl,
						     NULL,
						     _("Enter new NT password: "),
						     _("Retype new NT password: "),
						     (const char **)&pass_new);

			if (ret != PAM_SUCCESS) {
				_pam_log_debug(ctx, LOG_ALERT,
					       "password - "
					       "new password not obtained");
				pass_old = NULL;
				goto out;
			}


			if (pass_new[0] == '\0') {
				pass_new = NULL;
			}
		}


		_pam_get_data(pamh, PAM_WINBIND_PWD_LAST_SET,
			      &pwdlastset_update);


		if (cached_login) {
			ctx->ctrl |= WINBIND_CACHED_LOGIN;
		}

		ret = winbind_chauthtok_request(ctx, user, pass_old,
						pass_new, pwdlastset_update);
		if (ret) {
			pass_old = pass_new = NULL;
			goto out;
		}

		if (_pam_require_krb5_auth_after_chauthtok(ctx, user)) {

			const char *member = NULL;
			const char *cctype = NULL;
			int warn_pwd_expire;
			struct wbcLogonUserInfo *info = NULL;
			struct wbcUserPasswordPolicyInfo *policy = NULL;

			member = get_member_from_config(ctx);
			cctype = get_krb5_cc_type_from_config(ctx);
			warn_pwd_expire = get_warn_pwd_expire_from_config(ctx);


			ret = winbind_auth_request(ctx, user, pass_new,
						   member, cctype, 0,
						   &error, &info, &policy,
						   NULL, &username_ret);
			pass_old = pass_new = NULL;

			if (ret == PAM_SUCCESS) {

				struct wbcAuthUserInfo *user_info = NULL;

				if (info && info->info) {
					user_info = info->info;
				}


				_pam_warn_password_expiry(ctx, user_info, policy,
							  warn_pwd_expire,
							  NULL);


				_pam_set_data_info3(ctx, user_info);


				_pam_setup_krb5_env(ctx, info);

				if (username_ret) {
					pam_set_item(pamh, PAM_USER,
						     username_ret);
					_pam_log_debug(ctx, LOG_INFO,
						       "Returned user was '%s'",
						       username_ret);
					free(username_ret);
				}

				wbcFreeMemory(info);
				wbcFreeMemory(policy);
			}

			goto out;
		}
	} else {
		ret = PAM_SERVICE_ERR;
	}

out:
	{

		int i;
		const char *codes[] = {
			"NT_STATUS_DOMAIN_CONTROLLER_NOT_FOUND",
			"NT_STATUS_NO_LOGON_SERVERS",
			"NT_STATUS_ACCESS_DENIED"
		};

		for (i=0; i<ARRAY_SIZE(codes); i++) {
			int _ret;
			if (_pam_check_remark_auth_err(ctx, error, codes[i], &_ret)) {
				break;
			}
		}
	}

	wbcFreeMemory(error);

	_PAM_LOG_FUNCTION_LEAVE("pam_sm_chauthtok", ctx, ret);

	TALLOC_FREE(ctx);

	return ret;
}
