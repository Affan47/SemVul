sudoers_policy_close(int exit_status, int error_code)
{
    debug_decl(sudoers_policy_close, SUDOERS_DEBUG_PLUGIN);

    if (session_opened) {

	(void)sudo_auth_end_session(runas_pw);


	if (error_code) {
	    errno = error_code;
	    sudo_warn(U_("unable to execute %s"), safe_cmnd);
	}
    }


    sudo_fatal_callback_deregister(sudoers_cleanup);


    (void)env_init(NULL);


    if (sudo_user.pw != NULL) {
	sudo_pw_delref(sudo_user.pw);
	sudo_user.pw = NULL;
    }
    if (runas_pw != NULL) {
	sudo_pw_delref(runas_pw);
	runas_pw = NULL;
    }
    if (runas_gr != NULL) {
	sudo_gr_delref(runas_gr);
	runas_gr = NULL;
    }
    if (user_gid_list != NULL) {
	sudo_gidlist_delref(user_gid_list);
	user_gid_list = NULL;
    }
    free(user_gids);
    user_gids = NULL;
    free(audit_msg);
    audit_msg = NULL;


    sudoers_debug_deregister();
}
