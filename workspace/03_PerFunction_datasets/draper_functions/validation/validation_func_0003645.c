systemd_proxy_can_restart (SystemdProxy  *proxy,
                           gboolean      *can_restart,
                           GError       **error)
{
        PolkitAuthorizationResult *res;
        GError *local_error = NULL;

        *can_restart = FALSE;
        res = polkit_authority_check_authorization_sync (proxy->authority,
                                                         proxy->subject,
                                                         SYSTEMD_REBOOT_ACTION,
                                                         NULL,
                                                         POLKIT_CHECK_AUTHORIZATION_FLAGS_NONE,
                                                         NULL,
                                                         &local_error);
        if (res == NULL) {
                g_propagate_error (error, local_error);
                return FALSE;
        }

        *can_restart = polkit_authorization_result_get_is_authorized (res) ||
                       polkit_authorization_result_get_is_challenge (res);

        g_object_unref (res);

        return TRUE;
}
