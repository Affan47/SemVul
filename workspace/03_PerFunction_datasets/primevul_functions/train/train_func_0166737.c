auto_configure_outputs (GsdXrandrManager *manager, guint32 timestamp)
{
        GsdXrandrManagerPrivate *priv = manager->priv;
        GnomeRRConfig *config;
        int i;
        GList *just_turned_on;
        GList *l;
        int x;
        GError *error;

        config = gnome_rr_config_new_current (priv->rw_screen);


        just_turned_on = NULL;

        for (i = 0; config->outputs[i] != NULL; i++) {
                GnomeOutputInfo *output = config->outputs[i];

                if (output->connected && !output->on) {
                        output->on = TRUE;
                        output->rotation = GNOME_RR_ROTATION_0;
                        just_turned_on = g_list_prepend (just_turned_on, GINT_TO_POINTER (i));
                } else if (!output->connected && output->on)
                        output->on = FALSE;
        }


        x = 0;


        for (i = 0; config->outputs[i] != NULL; i++) {
                GnomeOutputInfo *output = config->outputs[i];

                if (g_list_find (just_turned_on, GINT_TO_POINTER (i)))
                        continue;

                if (output->on) {
                        g_assert (output->connected);

                        output->x = x;
                        output->y = 0;

                        x += output->width;
                }
        }


        for (l = just_turned_on; l; l = l->next) {
                GnomeOutputInfo *output;

                i = GPOINTER_TO_INT (l->data);
                output = config->outputs[i];

                g_assert (output->on && output->connected);

                output->x = x;
                output->y = 0;


                output->width = output->pref_width;
                output->height = output->pref_height;

                x += output->width;
        }


        error = NULL;
        if (!gnome_rr_config_apply_with_time (config, priv->rw_screen, timestamp, &error)) {
                error_message (manager, _("Could not switch the monitor configuration"), error, NULL);
                g_error_free (error);
        }

        g_list_free (just_turned_on);
        gnome_rr_config_free (config);


}
