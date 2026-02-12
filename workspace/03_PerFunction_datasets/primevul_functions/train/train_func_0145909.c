static htp_status_t htp_tx_process_request_headers(htp_tx_t *tx) {
    if (tx == NULL) return HTP_ERROR;


    htp_status_t rc = HTP_OK;

    htp_header_t *cl = htp_table_get_c(tx->request_headers, "content-length");
    htp_header_t *te = htp_table_get_c(tx->request_headers, "transfer-encoding");


    if (te != NULL) {


        if (bstr_cmp_c_nocase(te->value, "chunked") != 0) {

            tx->request_transfer_coding = HTP_CODING_INVALID;
            tx->flags |= HTP_REQUEST_INVALID_T_E;
            tx->flags |= HTP_REQUEST_INVALID;
        } else {


            if (tx->request_protocol_number < HTP_PROTOCOL_1_1) {
                tx->flags |= HTP_REQUEST_INVALID_T_E;
                tx->flags |= HTP_REQUEST_SMUGGLING;
            }


            tx->request_transfer_coding = HTP_CODING_CHUNKED;


            if (cl != NULL) {


                tx->flags |= HTP_REQUEST_SMUGGLING;
            }
        }
    } else if (cl != NULL) {

        if (cl->flags & HTP_FIELD_FOLDED) {
            tx->flags |= HTP_REQUEST_SMUGGLING;
        }


        if (cl->flags & HTP_FIELD_REPEATED) {
            tx->flags |= HTP_REQUEST_SMUGGLING;


        }


        tx->request_content_length = htp_parse_content_length(cl->value);
        if (tx->request_content_length < 0) {
            tx->request_transfer_coding = HTP_CODING_INVALID;
            tx->flags |= HTP_REQUEST_INVALID_C_L;
            tx->flags |= HTP_REQUEST_INVALID;
        } else {

            tx->request_transfer_coding = HTP_CODING_IDENTITY;
        }
    } else {

        tx->request_transfer_coding = HTP_CODING_NO_BODY;
    }


    if (tx->request_transfer_coding == HTP_CODING_UNKNOWN) {
        tx->request_transfer_coding = HTP_CODING_INVALID;
        tx->flags |= HTP_REQUEST_INVALID;
    }


    if (tx->request_method_number == HTP_M_PUT) {
        if (htp_tx_req_has_body(tx)) {


            tx->connp->put_file = calloc(1, sizeof (htp_file_t));
            if (tx->connp->put_file == NULL) return HTP_ERROR;

            tx->connp->put_file->fd = -1;
            tx->connp->put_file->source = HTP_FILE_PUT;
        } else {

        }
    }


    if (tx->parsed_uri->hostname != NULL) {
        tx->request_hostname = bstr_dup(tx->parsed_uri->hostname);
        if (tx->request_hostname == NULL) return HTP_ERROR;
    }

    tx->request_port_number = tx->parsed_uri->port_number;


    htp_header_t *h = htp_table_get_c(tx->request_headers, "host");
    if (h == NULL) {


        if (tx->request_protocol_number >= HTP_PROTOCOL_1_1) {
            tx->flags |= HTP_HOST_MISSING;
        }
    } else {


        bstr *hostname;
        int port;

        rc = htp_parse_header_hostport(h->value, &hostname, NULL, &port, &(tx->flags));
        if (rc != HTP_OK) return rc;

        if (hostname != NULL) {


            if (tx->request_hostname == NULL) {


                tx->request_hostname = hostname;
                tx->request_port_number = port;
            } else {


                if (bstr_cmp_nocase(hostname, tx->request_hostname) != 0) {
                    tx->flags |= HTP_HOST_AMBIGUOUS;
                }


                if (((tx->request_port_number != -1)&&(port != -1))&&(tx->request_port_number != port)) {
                    tx->flags |= HTP_HOST_AMBIGUOUS;
                }

                bstr_free(hostname);
            }
        } else {


            if (tx->request_hostname != NULL) {

                tx->flags |= HTP_HOST_AMBIGUOUS;
            }
        }
    }


    htp_header_t *ct = htp_table_get_c(tx->request_headers, "content-type");
    if (ct != NULL) {
        rc = htp_parse_ct_header(ct->value, &tx->request_content_type);
        if (rc != HTP_OK) return rc;
    }


    if (tx->connp->cfg->parse_request_cookies) {
        rc = htp_parse_cookies_v0(tx->connp);
        if (rc != HTP_OK) return rc;
    }


    if (tx->connp->cfg->parse_request_auth) {
        rc = htp_parse_authorization(tx->connp);
        if (rc == HTP_DECLINED) {

            tx->flags |= HTP_AUTH_INVALID;
        } else {
            if (rc != HTP_OK) return rc;
        }
    }


    rc = htp_connp_req_receiver_finalize_clear(tx->connp);
    if (rc != HTP_OK) return rc;


    rc = htp_hook_run_all(tx->connp->cfg->hook_request_headers, tx);
    if (rc != HTP_OK) return rc;


    if (tx->flags & HTP_REQUEST_INVALID) {
        return HTP_ERROR;
    }

    return HTP_OK;
}
