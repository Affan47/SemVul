make_laptop_setup (GnomeRRScreen *screen)
{

        GnomeRRConfig *result = gnome_rr_config_new_current (screen);
        int i;

        for (i = 0; result->outputs[i] != NULL; ++i) {
                GnomeOutputInfo *info = result->outputs[i];

                if (is_laptop (info)) {
                        if (!info->on) {
                                if (!turn_on (screen, info, 0, 0)) {
                                        gnome_rr_config_free (result);
                                        result = NULL;
                                        break;
                                }
                        }
                }
                else {
                        info->on = FALSE;
                }
        }

        print_configuration (result, "Laptop setup");


        return result;

}
