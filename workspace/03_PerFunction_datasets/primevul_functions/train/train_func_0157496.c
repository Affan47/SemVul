webSocketsDecodeHybi(ws_ctx_t *wsctx, char *dst, int len)
{
    int result = -1;


    ws_dbg("%s_enter: len=%d; "
                      "CTX: readlen=%d readPos=%p "
                      "writeTo=%p "
                      "state=%d payloadtoRead=%d payloadRemaining=%llu "
                      " nReadPayload=%d carrylen=%d carryBuf=%p\n",
                      __func__, len,
                      wsctx->readlen, wsctx->readPos,
                      wsctx->writePos,
                      wsctx->hybiDecodeState, wsctx->header.payloadLen, hybiRemaining(wsctx),
                      wsctx->nReadPayload, wsctx->carrylen, wsctx->carryBuf);

    switch (wsctx->hybiDecodeState){
      int nInBuf;
      case WS_HYBI_STATE_HEADER_PENDING:
        wsctx->hybiDecodeState = hybiReadHeader(wsctx, &result, &nInBuf);
        if (wsctx->hybiDecodeState == WS_HYBI_STATE_ERR) {
          goto spor;
        }
        if (wsctx->hybiDecodeState != WS_HYBI_STATE_HEADER_PENDING) {


          wsctx->hybiDecodeState = hybiReadAndDecode(wsctx, dst, len, &result, nInBuf);
        }
        break;
      case WS_HYBI_STATE_DATA_AVAILABLE:
        wsctx->hybiDecodeState = hybiReturnData(dst, len, wsctx, &result);
        break;
      case WS_HYBI_STATE_DATA_NEEDED:
        wsctx->hybiDecodeState = hybiReadAndDecode(wsctx, dst, len, &result, 0);
        break;
      case WS_HYBI_STATE_CLOSE_REASON_PENDING:
        wsctx->hybiDecodeState = hybiReadAndDecode(wsctx, dst, len, &result, 0);
        break;
      default:

        rfbErr("%s: called with invalid state %d\n", wsctx->hybiDecodeState);
        result = -1;
        errno = EIO;
        wsctx->hybiDecodeState = WS_HYBI_STATE_ERR;
    }


spor:
    if (wsctx->hybiDecodeState == WS_HYBI_STATE_FRAME_COMPLETE) {
      ws_dbg("frame received successfully, cleaning up: read=%d hlen=%d plen=%d\n", wsctx->header.nRead, wsctx->header.headerLen, wsctx->header.payloadLen);
      if (wsctx->header.fin && !isControlFrame(wsctx)) {

        hybiDecodeCleanupComplete(wsctx);
      } else {


        hybiDecodeCleanupForContinuation(wsctx);
      }
    } else if (wsctx->hybiDecodeState == WS_HYBI_STATE_ERR) {
      hybiDecodeCleanupComplete(wsctx);
    }

    ws_dbg("%s_exit: len=%d; "
                      "CTX: readlen=%d readPos=%p "
                      "writePos=%p "
                      "state=%d payloadtoRead=%d payloadRemaining=%d "
                      "nRead=%d carrylen=%d carryBuf=%p "
                      "result=%d "
                      "errno=%d\n",
                      __func__, len,
                      wsctx->readlen, wsctx->readPos,
                      wsctx->writePos,
                      wsctx->hybiDecodeState, wsctx->header.payloadLen, hybiRemaining(wsctx),
                      wsctx->nReadPayload, wsctx->carrylen, wsctx->carryBuf,
                      result,
                      errno);
    return result;
}
