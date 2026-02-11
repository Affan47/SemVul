UserDir()
    {
        static char user_dir[JACK_PATH_MAX + 1] = "";


        if (user_dir[0] == '\0') {
            if (getenv ("JACK_PROMISCUOUS_SERVER")) {
                snprintf(user_dir, sizeof(user_dir), "%s/jack", jack_tmpdir);
            } else {
                snprintf(user_dir, sizeof(user_dir), "%s/jack-%d", jack_tmpdir, GetUID());
            }
        }

        return user_dir;
    }
