relay_websocket_build_handshake (struct t_relay_client *client)
{
    const char *sec_websocket_key;
    char *key, sec_websocket_accept[128], handshake[1024], hash[160 / 8];
    int length, hash_size;

    sec_websocket_key = weechat_hashtable_get (client->http_headers,
                                               "sec-websocket-key");
    if (!sec_websocket_key || !sec_websocket_key[0])
        return NULL;

    length = strlen (sec_websocket_key) + strlen (WEBSOCKET_GUID) + 1;
    key = malloc (length);
    if (!key)
        return NULL;


    snprintf (key, length, "%s%s", sec_websocket_key, WEBSOCKET_GUID);


    if (!weechat_crypto_hash (key, strlen (key), "sha1", hash, &hash_size))
    {
        free (key);
        return NULL;
    }
    if (weechat_string_base_encode (64, hash, hash_size,
                                    sec_websocket_accept) < 0)
    {
        sec_websocket_accept[0] = '\0';
    }

    free (key);


    snprintf (handshake, sizeof (handshake),
              "HTTP/1.1 101 Switching Protocols\r\n"
              "Upgrade: websocket\r\n"
              "Connection: Upgrade\r\n"
              "Sec-WebSocket-Accept: %s\r\n"
              "\r\n",
              sec_websocket_accept);

    return strdup (handshake);
}
