sudoers_policy_validate(const char **errstr)
{
    int ret;
    debug_decl(sudoers_policy_validate, SUDOERS_DEBUG_PLUGIN);

    user_cmnd = "validate";
    SET(sudo_mode, MODE_VALIDATE);

    ret = sudoers_policy_main(0, NULL, I_VERIFYPW, NULL, false, NULL);


    if (ret != 1 && audit_msg != NULL) {
	if (sudo_version >= SUDO_API_MKVERSION(1, 15))
	    *errstr = audit_msg;
    }
    debug_return_int(ret);
}
