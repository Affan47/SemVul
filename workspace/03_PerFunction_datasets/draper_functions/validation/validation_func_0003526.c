gva_get_user_data_dir (void)
{
        static gchar *user_data_dir = NULL;

        if (G_UNLIKELY (user_data_dir == NULL))
        {
                user_data_dir = g_build_filename (
                        g_get_user_data_dir (), PACKAGE, NULL);

                if (g_mkdir_with_parents (user_data_dir, 0700) < 0)
                        g_warning (
                                "Unable to create %s: %s",
                                user_data_dir, g_strerror (errno));
        }

        return user_data_dir;
}
