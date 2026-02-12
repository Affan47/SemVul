htp_status_t htp_tx_state_request_line(htp_tx_t *tx) {
    if (tx == NULL) return HTP_ERROR;


    if (tx->request_method_number == HTP_M_CONNECT) {

        if (htp_parse_uri_hostport(tx->connp, tx->request_uri, tx->parsed_uri_raw) != HTP_OK) {
            return HTP_ERROR;
        }
    } else {

        if (htp_parse_uri(tx->request_uri, &(tx->parsed_uri_raw)) != HTP_OK) {
            return HTP_ERROR;
        }
    }


    if (tx->parsed_uri == NULL) {
        tx->parsed_uri = htp_uri_alloc();
        if (tx->parsed_uri == NULL) return HTP_ERROR;


        if (htp_normalize_parsed_uri(tx, tx->parsed_uri_raw, tx->parsed_uri) != HTP_OK) {
            return HTP_ERROR;
        }
    }


    if (tx->parsed_uri->hostname != NULL) {
        if (htp_validate_hostname(tx->parsed_uri->hostname) == 0) {
            tx->flags |= HTP_HOSTU_INVALID;
        }
    }


    htp_status_t rc = htp_hook_run_all(tx->connp->cfg->hook_request_uri_normalize, tx);
    if (rc != HTP_OK) return rc;


    rc = htp_hook_run_all(tx->connp->cfg->hook_request_line, tx);
    if (rc != HTP_OK) return rc;


    tx->connp->in_state = htp_connp_REQ_PROTOCOL;

    return HTP_OK;
}
