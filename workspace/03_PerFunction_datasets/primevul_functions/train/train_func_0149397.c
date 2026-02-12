static void _pam_warn_password_expiry(struct pwb_context *ctx,
				      const struct wbcAuthUserInfo *info,
				      const struct wbcUserPasswordPolicyInfo *policy,
				      int warn_pwd_expire,
				      bool *already_expired,
				      bool *change_pwd)
{
	time_t now = time(NULL);
	time_t next_change = 0;

	if (!info || !policy) {
		return;
	}

	if (already_expired) {
		*already_expired = false;
	}

	if (change_pwd) {
		*change_pwd = false;
	}


	if (info->acct_flags & WBC_ACB_PWNOEXP) {
		return;
	}


	if (PAM_WB_GRACE_LOGON(info->user_flags)) {
		return;
	}


	next_change = info->pass_must_change_time;

	if (_pam_send_password_expiry_message(ctx, next_change, now,
					      warn_pwd_expire,
					      already_expired,
					      change_pwd)) {
		return;
	}


	if ((policy->expire == (int64_t)-1) ||
	    (policy->expire == 0)) {
		return;
	}

	next_change = info->pass_last_set_time + policy->expire;

	if (_pam_send_password_expiry_message(ctx, next_change, now,
					      warn_pwd_expire,
					      already_expired,
					      change_pwd)) {
		return;
	}


}
