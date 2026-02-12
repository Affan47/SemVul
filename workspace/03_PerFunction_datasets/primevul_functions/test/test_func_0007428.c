static handler_t wstunnel_stdin_append(gw_handler_ctx *gwhctx) {


    handler_ctx *hctx = (handler_ctx *)gwhctx;
    if (0 == mod_wstunnel_frame_recv(hctx))
        return HANDLER_GO_ON;
    else {


        request_st * const r = hctx->gw.r;
        DEBUG_LOG_INFO("disconnected from client (fd=%d)", r->con->fd);
        DEBUG_LOG_DEBUG("send close response to client (fd=%d)", r->con->fd);
        mod_wstunnel_frame_send(hctx, MOD_WEBSOCKET_FRAME_TYPE_CLOSE, CONST_STR_LEN("1000"));
        gw_handle_request_reset(r, hctx->gw.plugin_data);
        return HANDLER_FINISHED;
    }
}
