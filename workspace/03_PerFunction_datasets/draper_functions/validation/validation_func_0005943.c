handle_connection(struct lwpb_transport_socket_server *socket_server,
        struct lwpb_socket_server_conn *conn)
{
    void *res_buf;
    size_t res_len;
    ssize_t len;
    size_t used;
    struct protocol_header_info info;
    lwpb_err_t ret;

    used = conn->pos - conn->buf;

    len = recv(conn->socket, conn->pos, conn->len - used, 0);
    if (len <= 0) {
        close_connection(socket_server, conn);
        return;
    }

    conn->pos += len;
    used = conn->pos - conn->buf;

    LWPB_DEBUG("Client(%d) received %d bytes", conn->index, len);


    ret = parse_request(conn->buf, used, &info, socket_server->server->service_list);
    if (ret != PARSE_ERR_OK)
        return;

    LWPB_DEBUG("Client(%d) received request header", conn->index);
    LWPB_DEBUG("type = %d, service = %p, method = %p, header_len = %d, msg_len = %d",
               info.msg_type, info.service_desc, info.method_desc,
               info.header_len, info.msg_len);

    if (!info.service_desc) {

    }

    if (!info.method_desc) {

    }


    ret = lwpb_transport_alloc_buf(&socket_server->super, &res_buf, &res_len);
    if (ret != LWPB_ERR_OK) {

    }

    ret = socket_server->server->call_handler(
        socket_server->server, info.method_desc,
        info.method_desc->req_desc,conn->buf + info.header_len, info.msg_len,
        info.method_desc->res_desc, res_buf, &res_len,
        socket_server->server->arg);


    send_response(conn->socket, info.method_desc, res_buf, res_len);

    lwpb_transport_free_buf(&socket_server->super, res_buf);
}
