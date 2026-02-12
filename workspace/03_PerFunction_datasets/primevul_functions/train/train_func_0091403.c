irc_server_set_host (struct t_irc_server *server, const char *host)
{
    struct t_irc_channel *ptr_channel;


    if ((!server->host && !host)
        || (server->host && host && strcmp (server->host, host) == 0))
    {
        return;
    }


    if (server->host)
        free (server->host);
    server->host = (host) ? strdup (host) : NULL;


    weechat_buffer_set (server->buffer, "localvar_set_host", host);
    for (ptr_channel = server->channels; ptr_channel;
         ptr_channel = ptr_channel->next_channel)
    {
        weechat_buffer_set (ptr_channel->buffer,
                            "localvar_set_host", host);
    }

    weechat_bar_item_update ("irc_host");
    weechat_bar_item_update ("irc_nick_host");
}
