int htp_tx_is_complete(htp_tx_t *tx) {
    if (tx == NULL) return -1;


    if ((tx->request_progress != HTP_REQUEST_COMPLETE) || (tx->response_progress != HTP_RESPONSE_COMPLETE)) {
        return 0;
    } else {
        return 1;
    }
}
