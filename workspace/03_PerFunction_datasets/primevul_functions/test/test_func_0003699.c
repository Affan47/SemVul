irc_protocol_nick_address (struct t_irc_server *server,
                           int server_message,
                           struct t_irc_nick *nick,
                           const char *nickname,
                           const char *address)
{
    static char string[1024];

    string[0] = '\0';

    if (nickname && address && (strcmp (nickname, address) != 0))
    {

        snprintf (string, sizeof (string),
                  "%s%s %s(%s%s%s)%s",
                  irc_nick_color_for_msg (server, server_message, nick,
                                          nickname),
                  nickname,
                  IRC_COLOR_CHAT_DELIMITERS,
                  IRC_COLOR_CHAT_HOST,
                  address,
                  IRC_COLOR_CHAT_DELIMITERS,
                  IRC_COLOR_RESET);
    }
    else if (nickname)
    {

        snprintf (string, sizeof (string),
                  "%s%s%s",
                  irc_nick_color_for_msg (server, server_message, nick,
                                          nickname),
                  nickname,
                  IRC_COLOR_RESET);
    }

    return string;
}
