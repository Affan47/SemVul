static int export_legacy_dbus_address(
                pam_handle_t *handle,
                uid_t uid,
                const char *runtime) {

        const char *s;
        _cleanup_free_ char *t = NULL;
        int r = PAM_BUF_ERR;


        s = strjoina(runtime, "/bus");
        if (access(s, F_OK) < 0)
                return PAM_SUCCESS;

        if (asprintf(&t, DEFAULT_USER_BUS_ADDRESS_FMT, runtime) < 0)
                goto error;

        r = pam_misc_setenv(handle, "DBUS_SESSION_BUS_ADDRESS", t, 0);
        if (r != PAM_SUCCESS)
                goto error;

        return PAM_SUCCESS;

error:
        pam_syslog(handle, LOG_ERR, "Failed to set bus variable.");
        return r;
}
