check_for_authentication(iscsi_session_t *session,
			 struct iscsi_acl *auth_client)
{
	enum iscsi_login_status ret = LOGIN_FAILED;

	auth_client = (struct iscsi_acl *)session->auth_buffers[0].address;


	if (acl_init(TYPE_INITIATOR, session->num_auth_buffers,
		     session->auth_buffers) != AUTH_STATUS_NO_ERROR) {
		log_error("Couldn't initialize authentication");
		return LOGIN_FAILED;
	}

	if (session->username &&
	    (acl_set_user_name(auth_client, session->username) !=
	    AUTH_STATUS_NO_ERROR)) {
		log_error("Couldn't set username");
		goto end;
	}

	if (session->password && (acl_set_passwd(auth_client,
	    session->password, session->password_length) !=
		 AUTH_STATUS_NO_ERROR)) {
		log_error("Couldn't set password");
		goto end;
	}

	if (acl_set_ip_sec(auth_client, 1) != AUTH_STATUS_NO_ERROR) {
		log_error("Couldn't set IPSec");
		goto end;
	}

	if (acl_set_auth_rmt(auth_client, session->bidirectional_auth) !=
			     AUTH_STATUS_NO_ERROR) {
		log_error("Couldn't set remote authentication");
		goto end;
	}
	return LOGIN_OK;

 end:
	if (auth_client && acl_finish(auth_client) != AUTH_STATUS_NO_ERROR) {
		log_error("Login failed, error finishing auth_client");
		if (ret == LOGIN_OK)
			ret = LOGIN_FAILED;
	}
	return ret;
}
