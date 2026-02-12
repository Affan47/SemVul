irc_protocol_recv_command (struct t_irc_server *server,
                           const char *irc_message,
                           const char *msg_command,
                           const char *msg_channel)
{
    int i, cmd_found, return_code, argc, decode_color, keep_trailing_spaces;
    int message_ignored, flags;
    char *message_colors_decoded, *pos_space, *tags;
    struct t_irc_channel *ptr_channel;
    t_irc_recv_func *cmd_recv_func;
    const char *cmd_name, *ptr_msg_after_tags;
    time_t date;
    const char *nick1, *address1, *host1;
    char *nick, *address, *address_color, *host, *host_no_color, *host_color;
    char **argv, **argv_eol;
    struct t_hashtable *hash_tags;
    struct t_irc_protocol_msg irc_protocol_messages[] =
        { { "account",  1, 0, &irc_protocol_cb_account },
          { "authenticate",  1, 0, &irc_protocol_cb_authenticate },
          { "away",  1, 0, &irc_protocol_cb_away },
          { "cap",  1, 0, &irc_protocol_cb_cap },
          { "chghost",  1, 0, &irc_protocol_cb_chghost },
          { "error",  1, 0, &irc_protocol_cb_error },
          { "invite",  1, 0, &irc_protocol_cb_invite },
          { "join",  1, 0, &irc_protocol_cb_join },
          { "kick",  1, 1, &irc_protocol_cb_kick },
          { "kill",  1, 1, &irc_protocol_cb_kill },
          { "mode",  1, 0, &irc_protocol_cb_mode },
          { "nick",  1, 0, &irc_protocol_cb_nick },
          { "notice",  1, 1, &irc_protocol_cb_notice },
          { "part",  1, 1, &irc_protocol_cb_part },
          { "ping",  1, 0, &irc_protocol_cb_ping },
          { "pong",  1, 0, &irc_protocol_cb_pong },
          { "privmsg",  1, 1, &irc_protocol_cb_privmsg },
          { "quit",  1, 1, &irc_protocol_cb_quit },
          { "topic",  0, 1, &irc_protocol_cb_topic },
          { "wallops",

 1, 1, &irc_protocol_cb_wallops },
          { "001",  1, 0, &irc_protocol_cb_001 },
          { "005",  1, 0, &irc_protocol_cb_005 },
          { "008",  1, 0, &irc_protocol_cb_008 },
          { "221",  1, 0, &irc_protocol_cb_221 },
          { "223",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "264",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "275",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "276",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "301",  1, 1, &irc_protocol_cb_301 },
          { "303",  1, 0, &irc_protocol_cb_303 },
          { "305",  1, 0, &irc_protocol_cb_305 },
          { "306",  1, 0, &irc_protocol_cb_306 },
          { "307",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "310",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "311",  1, 0, &irc_protocol_cb_311 },
          { "312",  1, 0, &irc_protocol_cb_312 },
          { "313",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "314",  1, 0, &irc_protocol_cb_314 },
          { "315",  1, 0, &irc_protocol_cb_315 },
          { "317",  1, 0, &irc_protocol_cb_317 },
          { "318",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "319",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "320",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "321",  1, 0, &irc_protocol_cb_321 },
          { "322",  1, 0, &irc_protocol_cb_322 },
          { "323",  1, 0, &irc_protocol_cb_323 },
          { "324",  1, 0, &irc_protocol_cb_324 },
          { "326",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "327",  1, 0, &irc_protocol_cb_327 },
          { "328",  1, 0, &irc_protocol_cb_328 },
          { "329",  1, 0, &irc_protocol_cb_329 },
          { "330",  1, 0, &irc_protocol_cb_330_343 },
          { "331",  1, 0, &irc_protocol_cb_331 },
          { "332",  0, 1, &irc_protocol_cb_332 },
          { "333",  1, 0, &irc_protocol_cb_333 },
          { "335",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "338",  1, 0, &irc_protocol_cb_338 },
          { "341",  1, 0, &irc_protocol_cb_341 },
          { "343",  1, 0, &irc_protocol_cb_330_343 },
          { "344",  1, 0, &irc_protocol_cb_344 },
          { "345",  1, 0, &irc_protocol_cb_345 },
          { "346",  1, 0, &irc_protocol_cb_346 },
          { "347",  1, 0, &irc_protocol_cb_347 },
          { "348",  1, 0, &irc_protocol_cb_348 },
          { "349",  1, 0, &irc_protocol_cb_349 },
          { "351",  1, 0, &irc_protocol_cb_351 },
          { "352",  1, 0, &irc_protocol_cb_352 },
          { "353",  1, 0, &irc_protocol_cb_353 },
          { "354",  1, 0, &irc_protocol_cb_354 },
          { "366",  1, 0, &irc_protocol_cb_366 },
          { "367",  1, 0, &irc_protocol_cb_367 },
          { "368",  1, 0, &irc_protocol_cb_368 },
          { "369",  1, 0, &irc_protocol_cb_whowas_nick_msg },
          { "378",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "379",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "401",  1, 0, &irc_protocol_cb_generic_error },
          { "402",  1, 0, &irc_protocol_cb_generic_error },
          { "403",  1, 0, &irc_protocol_cb_generic_error },
          { "404",  1, 0, &irc_protocol_cb_generic_error },
          { "405",  1, 0, &irc_protocol_cb_generic_error },
          { "406",  1, 0, &irc_protocol_cb_generic_error },
          { "407",  1, 0, &irc_protocol_cb_generic_error },
          { "409",  1, 0, &irc_protocol_cb_generic_error },
          { "410",  1, 0, &irc_protocol_cb_generic_error },
          { "411",  1, 0, &irc_protocol_cb_generic_error },
          { "412",  1, 0, &irc_protocol_cb_generic_error },
          { "413",  1, 0, &irc_protocol_cb_generic_error },
          { "414",  1, 0, &irc_protocol_cb_generic_error },
          { "421",  1, 0, &irc_protocol_cb_generic_error },
          { "422",  1, 0, &irc_protocol_cb_generic_error },
          { "423",  1, 0, &irc_protocol_cb_generic_error },
          { "424",  1, 0, &irc_protocol_cb_generic_error },
          { "431",  1, 0, &irc_protocol_cb_generic_error },
          { "432",  1, 0, &irc_protocol_cb_432 },
          { "433",  1, 0, &irc_protocol_cb_433 },
          { "436",  1, 0, &irc_protocol_cb_generic_error },
          { "437",  1, 0, &irc_protocol_cb_437 },
          { "438",  1, 0, &irc_protocol_cb_438 },
          { "441",  1, 0, &irc_protocol_cb_generic_error },
          { "442",  1, 0, &irc_protocol_cb_generic_error },
          { "443",  1, 0, &irc_protocol_cb_generic_error },
          { "444",  1, 0, &irc_protocol_cb_generic_error },
          { "445",  1, 0, &irc_protocol_cb_generic_error },
          { "446",  1, 0, &irc_protocol_cb_generic_error },
          { "451",  1, 0, &irc_protocol_cb_generic_error },
          { "461",  1, 0, &irc_protocol_cb_generic_error },
          { "462",  1, 0, &irc_protocol_cb_generic_error },
          { "463",  1, 0, &irc_protocol_cb_generic_error },
          { "464",  1, 0, &irc_protocol_cb_generic_error },
          { "465",  1, 0, &irc_protocol_cb_generic_error },
          { "467",  1, 0, &irc_protocol_cb_generic_error },
          { "470",  1, 0, &irc_protocol_cb_470 },
          { "471",  1, 0, &irc_protocol_cb_generic_error },
          { "472",  1, 0, &irc_protocol_cb_generic_error },
          { "473",  1, 0, &irc_protocol_cb_generic_error },
          { "474",  1, 0, &irc_protocol_cb_generic_error },
          { "475",  1, 0, &irc_protocol_cb_generic_error },
          { "476",  1, 0, &irc_protocol_cb_generic_error },
          { "477",  1, 0, &irc_protocol_cb_generic_error },
          { "481",  1, 0, &irc_protocol_cb_generic_error },
          { "482",  1, 0, &irc_protocol_cb_generic_error },
          { "483",  1, 0, &irc_protocol_cb_generic_error },
          { "484",  1, 0, &irc_protocol_cb_generic_error },
          { "485",  1, 0, &irc_protocol_cb_generic_error },
          { "487",  1, 0, &irc_protocol_cb_generic_error },
          { "491",  1, 0, &irc_protocol_cb_generic_error },
          { "501",  1, 0, &irc_protocol_cb_generic_error },
          { "502",  1, 0, &irc_protocol_cb_generic_error },
          { "671",  1, 0, &irc_protocol_cb_whois_nick_msg },
          { "728",  1, 0, &irc_protocol_cb_728 },
          { "729",  1, 0, &irc_protocol_cb_729 },
          { "730",  1, 0, &irc_protocol_cb_730 },
          { "731",  1, 0, &irc_protocol_cb_731 },
          { "732",  1, 0, &irc_protocol_cb_732 },
          { "733",  1, 0, &irc_protocol_cb_733 },
          { "734",  1, 0, &irc_protocol_cb_734 },
          { "900",  1, 0, &irc_protocol_cb_900 },
          { "901",  1, 0, &irc_protocol_cb_901 },
          { "902",  1, 0, &irc_protocol_cb_sasl_end_fail },
          { "903",  1, 0, &irc_protocol_cb_sasl_end_ok },
          { "904",  1, 0, &irc_protocol_cb_sasl_end_fail },
          { "905",  1, 0, &irc_protocol_cb_sasl_end_fail },
          { "906",  1, 0, &irc_protocol_cb_sasl_end_fail },
          { "907",  1, 0, &irc_protocol_cb_sasl_end_ok },
          { "936",  1, 0, &irc_protocol_cb_generic_error },
          { "973",  1, 0, &irc_protocol_cb_server_mode_reason },
          { "974",  1, 0, &irc_protocol_cb_server_mode_reason },
          { "975",  1, 0, &irc_protocol_cb_server_mode_reason },
          { NULL, 0, 0, NULL }
        };

    if (!msg_command)
        return;

    message_colors_decoded = NULL;
    argv = NULL;
    argv_eol = NULL;
    hash_tags = NULL;
    date = 0;

    ptr_msg_after_tags = irc_message;


    if (irc_message && (irc_message[0] == '@'))
    {
        pos_space = strchr (irc_message, ' ');
        if (pos_space)
        {
            tags = weechat_strndup (irc_message + 1,
                                    pos_space - (irc_message + 1));
            if (tags)
            {
                hash_tags = irc_protocol_get_message_tags (tags);
                if (hash_tags)
                {
                    date = irc_protocol_parse_time (
                        weechat_hashtable_get (hash_tags, "time"));
                }
                free (tags);
            }
            ptr_msg_after_tags = pos_space;
            while (ptr_msg_after_tags[0] == ' ')
            {
                ptr_msg_after_tags++;
            }
        }
        else
            ptr_msg_after_tags = NULL;
    }


    nick1 = NULL;
    address1 = NULL;
    host1 = NULL;
    if (ptr_msg_after_tags && (ptr_msg_after_tags[0] == ':'))
    {
        nick1 = irc_message_get_nick_from_host (ptr_msg_after_tags);
        address1 = irc_message_get_address_from_host (ptr_msg_after_tags);
        host1 = ptr_msg_after_tags + 1;
    }
    nick = (nick1) ? strdup (nick1) : NULL;
    address = (address1) ? strdup (address1) : NULL;
    address_color = (address) ?
        irc_color_decode (
            address,
            weechat_config_boolean (irc_config_network_colors_receive)) :
        NULL;
    host = (host1) ? strdup (host1) : NULL;
    if (host)
    {
        pos_space = strchr (host, ' ');
        if (pos_space)
            pos_space[0] = '\0';
    }
    host_no_color = (host) ? irc_color_decode (host, 0) : NULL;
    host_color = (host) ?
        irc_color_decode (
            host,
            weechat_config_boolean (irc_config_network_colors_receive)) :
        NULL;


    ptr_channel = NULL;
    if (msg_channel)
        ptr_channel = irc_channel_search (server, msg_channel);
    message_ignored = irc_ignore_check (
        server,
        (ptr_channel) ? ptr_channel->name : msg_channel,
        nick, host_no_color);


    irc_server_send_signal (server, "irc_raw_in", msg_command,
                            irc_message, NULL);


    if (!message_ignored)
    {
        irc_server_send_signal (server, "irc_in", msg_command,
                                irc_message, NULL);
    }


    cmd_found = -1;
    for (i = 0; irc_protocol_messages[i].name; i++)
    {
        if (weechat_strcasecmp (irc_protocol_messages[i].name,
                                msg_command) == 0)
        {
            cmd_found = i;
            break;
        }
    }


    if (cmd_found < 0)
    {

        if (irc_protocol_is_numeric_command (msg_command))
        {
            cmd_name = msg_command;
            decode_color = 1;
            keep_trailing_spaces = 0;
            cmd_recv_func = irc_protocol_cb_numeric;
        }
        else
        {
            weechat_printf (server->buffer,
                            _("%s%s: command \"%s\" not found:"),
                            weechat_prefix ("error"), IRC_PLUGIN_NAME,
                            msg_command);
            weechat_printf (server->buffer,
                            "%s%s",
                            weechat_prefix ("error"), irc_message);
            goto end;
        }
    }
    else
    {
        cmd_name = irc_protocol_messages[cmd_found].name;
        decode_color = irc_protocol_messages[cmd_found].decode_color;
        keep_trailing_spaces = irc_protocol_messages[cmd_found].keep_trailing_spaces;
        cmd_recv_func = irc_protocol_messages[cmd_found].recv_function;
    }

    if (cmd_recv_func != NULL)
    {
        if (ptr_msg_after_tags)
        {
            if (decode_color)
            {
                message_colors_decoded = irc_color_decode (
                    ptr_msg_after_tags,
                    weechat_config_boolean (irc_config_network_colors_receive));
            }
            else
            {
                message_colors_decoded = strdup (ptr_msg_after_tags);
            }
        }
        else
            message_colors_decoded = NULL;
        argv = weechat_string_split (message_colors_decoded, " ", NULL,
                                     WEECHAT_STRING_SPLIT_STRIP_LEFT
                                     | WEECHAT_STRING_SPLIT_STRIP_RIGHT
                                     | WEECHAT_STRING_SPLIT_COLLAPSE_SEPS,
                                     0, &argc);
        flags = WEECHAT_STRING_SPLIT_STRIP_LEFT
            | WEECHAT_STRING_SPLIT_COLLAPSE_SEPS
            | WEECHAT_STRING_SPLIT_KEEP_EOL;
        if (keep_trailing_spaces)
            flags |= WEECHAT_STRING_SPLIT_STRIP_RIGHT;
        argv_eol = weechat_string_split (message_colors_decoded, " ", NULL,
                                         flags, 0, NULL);

        return_code = (int) (cmd_recv_func) (server,
                                             date, nick, address_color,
                                             host_color, cmd_name,
                                             message_ignored, argc, argv,
                                             argv_eol);

        if (return_code == WEECHAT_RC_ERROR)
        {
            weechat_printf (server->buffer,
                            _("%s%s: failed to parse command \"%s\" (please "
                              "report to developers):"),
                            weechat_prefix ("error"), IRC_PLUGIN_NAME,
                            msg_command);
            weechat_printf (server->buffer,
                            "%s%s",
                            weechat_prefix ("error"), irc_message);
        }


        if (!message_ignored)
        {
            irc_server_send_signal (server, "irc_in2", msg_command,
                                    irc_message, NULL);
        }
    }


    irc_server_send_signal (server, "irc_raw_in2", msg_command,
                            irc_message, NULL);

end:
    if (nick)
        free (nick);
    if (address)
        free (address);
    if (address_color)
        free (address_color);
    if (host)
        free (host);
    if (host_no_color)
        free (host_no_color);
    if (host_color)
        free (host_color);
    if (message_colors_decoded)
        free (message_colors_decoded);
    if (argv)
        weechat_string_free_split (argv);
    if (argv_eol)
        weechat_string_free_split (argv_eol);
    if (hash_tags)
        weechat_hashtable_free (hash_tags);
}
