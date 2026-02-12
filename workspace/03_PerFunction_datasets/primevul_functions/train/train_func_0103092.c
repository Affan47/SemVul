irc_mode_get_chanmode_type (struct t_irc_server *server, char chanmode)
{
    char chanmode_type, *pos;
    const char *chanmodes, *ptr_chanmodes;


    if (irc_server_get_prefix_mode_index (server, chanmode) >= 0)
        return 'B';

    chanmodes = irc_server_get_chanmodes (server);
    pos = strchr (chanmodes, chanmode);
    if (pos)
    {
        chanmode_type = 'A';
        for (ptr_chanmodes = chanmodes; ptr_chanmodes < pos; ptr_chanmodes++)
        {
            if (ptr_chanmodes[0] == ',')
            {
                if (chanmode_type == 'D')
                    break;
                chanmode_type++;
            }
        }
        return chanmode_type;
    }


    return 'D';
}
