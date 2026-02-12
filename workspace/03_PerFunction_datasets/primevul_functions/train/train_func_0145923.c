htp_status_t htp_tx_finalize(htp_tx_t *tx) {
    if (tx == NULL) return HTP_ERROR;

    if (!htp_tx_is_complete(tx)) return HTP_OK;


    htp_status_t rc = htp_hook_run_all(tx->connp->cfg->hook_transaction_complete, tx);
    if (rc != HTP_OK) return rc;


    if (tx->connp->cfg->tx_auto_destroy) {
        htp_tx_destroy(tx);
    }

    return HTP_OK;
}
