relay_websocket_save_header (struct t_relay_client *client,
                             const char *message)
{
    char *pos, *name;
    const char *ptr_value;


    if (strncmp (message, "GET ", 4) == 0)
        return;

    pos = strchr (message, ':');


    if (!pos || (pos == message))
        return;


    name = weechat_strndup (message, pos - message);
    if (!name)
        return;
    weechat_string_tolower (name);


    ptr_value = pos + 1;
    while (ptr_value[0] == ' ')
    {
        ptr_value++;
    }


    weechat_hashtable_set (client->http_headers, name, ptr_value);

    free (name);
}
