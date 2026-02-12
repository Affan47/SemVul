PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, CONST char **argv)
{
	CONST char *user;
	char *password = NULL;
	char *new_password = NULL;
	char *check_password = NULL;
	int ctrl;
	int retval = PAM_AUTHTOK_ERR;
	int attempts;

	char recv_buffer[4096];
	char send_buffer[4096];
	AUTH_HDR *request = (AUTH_HDR *) send_buffer;
	AUTH_HDR *response = (AUTH_HDR *) recv_buffer;
	radius_conf_t config;

	ctrl = _pam_parse(argc, argv, &config);


	retval = pam_get_user(pamh, &user, NULL);
	PAM_FAIL_CHECK;


	if ((user == NULL) || (strlen(user) > MAXPWNAM)) {
		return PAM_USER_UNKNOWN;
	}


	retval = initialize(&config, FALSE);
	PAM_FAIL_CHECK;


	if (!config.client_id) {
		retval = pam_get_item(pamh, PAM_SERVICE, (CONST void **) &config.client_id);
		PAM_FAIL_CHECK;
	}


#undef PAM_FAIL_CHECK
#define PAM_FAIL_CHECK if (retval != PAM_SUCCESS) {goto error; }


	retval = pam_get_item(pamh, PAM_OLDAUTHTOK, (CONST void **) &password);
	PAM_FAIL_CHECK;
	if (password) password = strdup(password);


	retval = pam_get_item(pamh, PAM_AUTHTOK, (CONST void **) &new_password);
	PAM_FAIL_CHECK;
	if (new_password) new_password = strdup(new_password);


	if (flags & PAM_PRELIM_CHECK) {
		if (!password) {
			retval = rad_converse(pamh, PAM_PROMPT_ECHO_OFF, config.prompt, &password);
			PAM_FAIL_CHECK;
		}


		request->code = PW_AUTHENTICATION_REQUEST;
		get_random_vector(request->vector);
		request->id = request->vector[0];

		build_radius_packet(request, user, password, &config);
		add_int_attribute(request, PW_USER_SERVICE_TYPE, PW_AUTHENTICATE_ONLY);

		retval = talk_radius(&config, request, response, password, NULL, 1);
		PAM_FAIL_CHECK;


		if (response->code != PW_AUTHENTICATION_ACK) {
			_pam_forget(password);
			retval = PAM_PERM_DENIED;
			goto error;
		}


		if (!new_password) {
			int new_attempts;
			attempts = 0;


			while (attempts++ < 3) {


				new_attempts = 0;
				while (new_attempts++ < 3) {
					retval = rad_converse(pamh, PAM_PROMPT_ECHO_OFF,
							"New password: ", &new_password);
					PAM_FAIL_CHECK;


					if (strcmp(password, new_password) == 0) {
						rad_converse(pamh, PAM_ERROR_MSG,
						 "You must choose a new password.", NULL);
						_pam_forget(new_password);
						continue;
					} else if (strlen(new_password) < 6) {
						rad_converse(pamh, PAM_ERROR_MSG, "it's WAY too short", NULL);
						_pam_forget(new_password);
						continue;
					}


					break;
				}

				if (new_attempts >= 3) {
					retval = PAM_AUTHTOK_ERR;
					goto error;
				}


				retval = rad_converse(pamh, PAM_PROMPT_ECHO_OFF,
						      "New password (again): ", &check_password);
				PAM_FAIL_CHECK;

				retval = strcmp(new_password, check_password);
				_pam_forget(check_password);


				if (retval != 0) {
					_pam_forget(new_password);
					rad_converse(pamh, PAM_ERROR_MSG,
								 "You must enter the same password twice.", NULL);
					retval = PAM_AUTHTOK_ERR;
					goto error;
				}

				break;
			}

			if (attempts >= 3) {
				retval = PAM_AUTHTOK_ERR;
				goto error;
			}
		}


#ifndef sun

	} else if (flags & PAM_UPDATE_AUTHTOK) {
#endif

		if (!password || !new_password) {
			retval = PAM_AUTHTOK_ERR;
			goto error;
		}


		request->code = PW_PASSWORD_REQUEST;
		get_random_vector(request->vector);
		request->id = request->vector[0];


		_pam_forget(config.server->secret);
		config.server->secret = strdup(password);

		build_radius_packet(request, user, new_password, &config);
		add_password(request, PW_OLD_PASSWORD, password, password);

		retval = talk_radius(&config, request, response, new_password, password, 1);
		PAM_FAIL_CHECK;


		if (response->code != PW_PASSWORD_ACK) {
			retval = PAM_AUTHTOK_ERR;
			goto error;
		}
	}


	if ((flags & PAM_PRELIM_CHECK) || (retval != PAM_SUCCESS)) {
	error:


		if (password && *password) {
			pam_set_item(pamh, PAM_OLDAUTHTOK, password);
		}

		if (new_password && *new_password) {
			pam_set_item(pamh, PAM_AUTHTOK, new_password);
		}
	}

	if (ctrl & PAM_DEBUG_ARG) {
		_pam_log(LOG_DEBUG, "password change %s", retval==PAM_SUCCESS ? "succeeded" : "failed");
	}

	close(config.sockfd);
	cleanup(config.server);

	_pam_forget(password);
	_pam_forget(new_password);
	return retval;
}
