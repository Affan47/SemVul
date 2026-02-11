cimd2_login(SMSCConn *conn)
{
    PrivData *pdata = conn->data;
    int ret;
    struct packet *packet = NULL;

    gw_assert(pdata != NULL);

    if (pdata->socket >= 0) {
        warning(0, "CIMD2[%s]: login: socket was already open; closing",
                octstr_get_cstr(conn->id));
        cimd2_close_socket(pdata);
    }

    pdata->socket = tcpip_connect_to_server_with_port(
                                            octstr_get_cstr(pdata->host),
                                            pdata->port,
                                            pdata->our_port,
                                            (conn->our_host ? octstr_get_cstr(conn->our_host) : NULL));
    if (pdata->socket != -1) {

        packet = packet_create(LOGIN, BOGUS_SEQUENCE);
        packet_add_string_parm(packet, P_USER_IDENTITY, pdata->username, conn);
        packet_add_string_parm(packet, P_PASSWORD, pdata->password, conn);

        ret = cimd2_request(packet, conn, NULL);

        if (ret >= 0) {
            packet_destroy(packet);
            info(0, "CIMD2[%s] logged in.",
                 octstr_get_cstr(conn->id));
            return 0;
        }
    }
    error(0, "CIMD2[%s] login failed.",
          octstr_get_cstr(conn->id));
    cimd2_close_socket(pdata);
    packet_destroy(packet);
    return -1;
}
