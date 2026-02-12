irc_mode_smart_filtered (struct t_irc_server *server, char mode)
{
    const char *ptr_modes;

    ptr_modes = weechat_config_string (irc_config_look_smart_filter_mode);


    if (!ptr_modes || !ptr_modes[0])
        return 0;


    if (strcmp (ptr_modes, "*") == 0)
        return 1;


    if (strcmp (ptr_modes, "+") == 0)
        return strchr (irc_server_get_prefix_modes (server), mode) ? 1 : 0;


    if (ptr_modes[0] == '-')
        return (strchr (ptr_modes + 1, mode)) ? 0 : 1;


    return (strchr (ptr_modes, mode)) ? 1 : 0;
}
