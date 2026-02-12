ensure_current_configuration_is_saved (void)
{
        GnomeRRScreen *rr_screen;
        GnomeRRConfig *rr_config;


        rr_screen = gnome_rr_screen_new (gdk_screen_get_default (), NULL, NULL, NULL);
        if (!rr_screen)
                return;

        rr_config = gnome_rr_config_new_current (rr_screen);
        gnome_rr_config_save (rr_config, NULL);

        gnome_rr_config_free (rr_config);
        gnome_rr_screen_destroy (rr_screen);
}
