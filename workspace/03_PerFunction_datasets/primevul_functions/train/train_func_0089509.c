relay_websocket_is_http_get_weechat (const char *message)
{

    if (strncmp (message, "GET /weechat", 12) != 0)
        return 0;


    if ((message[12] != '\r') && (message[12] != '\n')
        && (strncmp (message + 12, " HTTP", 5) != 0))
    {
        return 0;
    }


    return 1;
}
