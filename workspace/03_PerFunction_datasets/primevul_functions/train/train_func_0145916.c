htp_status_t htp_tx_state_response_complete_ex(htp_tx_t *tx, int hybrid_mode) {
    if (tx == NULL) return HTP_ERROR;

    if (tx->response_progress != HTP_RESPONSE_COMPLETE) {
        tx->response_progress = HTP_RESPONSE_COMPLETE;


        if (tx->response_transfer_coding != HTP_CODING_NO_BODY) {
            htp_tx_res_process_body_data_ex(tx, NULL, 0);
        }


        htp_status_t rc = htp_hook_run_all(tx->connp->cfg->hook_response_complete, tx);
        if (rc != HTP_OK) return rc;
    }

    if (!hybrid_mode) {


        if ((tx->connp->in_status == HTP_STREAM_DATA_OTHER) && (tx->connp->in_tx == tx->connp->out_tx)) {
            return HTP_DATA_OTHER;
        }


        if (tx->connp->out_data_other_at_tx_end) {

            tx->connp->out_data_other_at_tx_end = 0;
            return HTP_DATA_OTHER;
        }
    }


    htp_connp_t *connp = tx->connp;


    htp_status_t rc = htp_tx_finalize(tx);
    if (rc != HTP_OK) return rc;


    connp->out_tx = NULL;

    connp->out_state = htp_connp_RES_IDLE;

    return HTP_OK;
}
