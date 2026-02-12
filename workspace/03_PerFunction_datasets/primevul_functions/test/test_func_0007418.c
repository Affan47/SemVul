static int create_response_ietf_00(handler_ctx *hctx) {
    request_st * const r = hctx->gw.r;


    const buffer *origin = http_header_request_get(r, HTTP_HEADER_OTHER, CONST_STR_LEN("Origin"));
    if (NULL == origin) {
        origin =
          http_header_request_get(r, HTTP_HEADER_OTHER, CONST_STR_LEN("Sec-WebSocket-Origin"));
    }
    if (NULL == origin) {
        DEBUG_LOG_ERR("%s", "Origin header is invalid");
        return -1;
    }
    if (!r->http_host || buffer_is_blank(r->http_host)) {
        DEBUG_LOG_ERR("%s", "Host header does not exist");
        return -1;
    }


    if (create_MD5_sum(r) < 0) {
        DEBUG_LOG_ERR("%s", "Sec-WebSocket-Key is invalid");
        return -1;
    }

    http_header_response_set(r, HTTP_HEADER_UPGRADE,
                             CONST_STR_LEN("Upgrade"),
                             CONST_STR_LEN("websocket"));
  #if 0
    http_header_response_append(r, HTTP_HEADER_CONNECTION,
                                CONST_STR_LEN("Connection"),
                                CONST_STR_LEN("upgrade"));
  #endif
  #if 0


    http_header_response_set(r, HTTP_HEADER_OTHER,
                             CONST_STR_LEN("Sec-WebSocket-Origin"),
                             BUF_PTR_LEN(origin));
  #endif

    buffer * const value =
      http_header_response_set_ptr(r, HTTP_HEADER_OTHER,
                                   CONST_STR_LEN("Sec-WebSocket-Location"));
    if (buffer_is_equal_string(&r->uri.scheme, CONST_STR_LEN("https")))
        buffer_copy_string_len(value, CONST_STR_LEN("wss://"));
    else
        buffer_copy_string_len(value, CONST_STR_LEN("ws://"));
    buffer_append_str2(value, BUF_PTR_LEN(r->http_host),
                              BUF_PTR_LEN(&r->uri.path));
    return 0;
}
