on_randr_event (GnomeRRScreen *screen, gpointer data)
{
        GsdXrandrManager *manager = GSD_XRANDR_MANAGER (data);
        GsdXrandrManagerPrivate *priv = manager->priv;
        guint32 change_timestamp, config_timestamp;

        if (!priv->running)
                return;

        gnome_rr_screen_get_timestamps (screen, &change_timestamp, &config_timestamp);

        if (change_timestamp > config_timestamp) {


                show_timestamps_dialog (manager, "ignoring since change > config");
        } else {


#if 1
                auto_configure_outputs (manager, config_timestamp);
#else


                char *intended_filename;
                GError *error;
                gboolean success;

                show_timestamps_dialog (manager, "need to deal with reconfiguration, as config >= change");

                intended_filename = gnome_rr_config_get_intended_filename ();

                error = NULL;
                success = apply_configuration_from_filename (manager, intended_filename, TRUE, config_timestamp, &error);
                g_free (intended_filename);

                if (!success) {


                        if (error)
                                g_error_free (error);

                        auto_configure_outputs (manager, config_timestamp);
                }
#endif
        }

        refresh_tray_icon_menu_if_active (manager, MAX (change_timestamp, config_timestamp));
}
