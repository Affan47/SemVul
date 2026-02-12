handler_t mod_wstunnel_handshake_create_response(handler_ctx *hctx) {
    request_st * const r = hctx->gw.r;
  #ifdef _MOD_WEBSOCKET_SPEC_RFC_6455_
    if (hctx->hybivers >= 8) {
        DEBUG_LOG_DEBUG("%s", "send handshake response");
        if (0 != create_response_rfc_6455(hctx)) {
            r->http_status = 400;
            return HANDLER_ERROR;
        }
        return HANDLER_GO_ON;
    }
  #endif

  #ifdef _MOD_WEBSOCKET_SPEC_IETF_00_
    if (hctx->hybivers == 0 && r->http_version == HTTP_VERSION_1_1) {
      #ifdef _MOD_WEBSOCKET_SPEC_IETF_00_


        chunkqueue *cq = &r->reqbody_queue;
        if (chunkqueue_length(cq) < 8)
            return HANDLER_WAIT_FOR_EVENT;
      #endif

        DEBUG_LOG_DEBUG("%s", "send handshake response");
        if (0 != create_response_ietf_00(hctx)) {
            r->http_status = 400;
            return HANDLER_ERROR;
        }
        return HANDLER_GO_ON;
    }
  #endif

    DEBUG_LOG_ERR("%s", "not supported WebSocket Version");
    r->http_status = 503;
    return HANDLER_ERROR;
}
