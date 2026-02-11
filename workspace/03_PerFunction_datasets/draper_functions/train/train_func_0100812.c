daemon_init (Daemon *daemon)
{
        daemon->priv = DAEMON_GET_PRIVATE (daemon);

        daemon->priv->extension_ifaces = daemon_read_extension_ifaces ();

        daemon->priv->users = create_users_hash_table ();

        daemon->priv->passwd_monitor = setup_monitor (daemon,
                                                      PATH_PASSWD,
                                                      on_users_monitor_changed);
        daemon->priv->shadow_monitor = setup_monitor (daemon,
                                                      PATH_SHADOW,
                                                      on_users_monitor_changed);
        daemon->priv->group_monitor = setup_monitor (daemon,
                                                     PATH_GROUP,
                                                     on_users_monitor_changed);

#ifdef HAVE_UTMPX_H
        daemon->priv->wtmp_monitor = setup_monitor (daemon,
                                                    PATH_WTMP,
                                                    on_users_monitor_changed);
#endif

        if (g_file_test ("/etc/gdm", G_FILE_TEST_EXISTS))
        {
                daemon->priv->gdm_monitor = setup_monitor (daemon,
                                                           PATH_GDM_CUSTOM,
                                                           on_gdm_monitor_changed);
        }

        if (g_file_test ("/etc/lightdm", G_FILE_TEST_EXISTS))
        {
                daemon->priv->lightdm_monitor = setup_monitor (daemon,
                                                           PATH_LIGHTDM_CONFIG,
                                                           on_gdm_monitor_changed);
        }

        queue_reload_users (daemon);
        queue_reload_autologin (daemon);
}
