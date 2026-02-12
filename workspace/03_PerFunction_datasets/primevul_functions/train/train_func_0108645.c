void esp_transfer_data(SCSIRequest *req, uint32_t len)
{
    ESPState *s = req->hba_private;
    int to_device = ((s->rregs[ESP_RSTAT] & 7) == STAT_DO);
    uint32_t dmalen = esp_get_tc(s);

    assert(!s->do_cmd);
    trace_esp_transfer_data(dmalen, s->ti_size);
    s->async_len = len;
    s->async_buf = scsi_req_get_buf(req);

    if (!to_device && !s->data_in_ready) {


        s->data_in_ready = true;
        s->rregs[ESP_RSTAT] |= STAT_TC;
        s->rregs[ESP_RINTR] |= INTR_BS;
        esp_raise_irq(s);


        if (s->ti_size && (s->rregs[ESP_CMD] == (CMD_TI | CMD_DMA))) {
            esp_do_dma(s);
        }
        return;
    }

    if (s->ti_cmd == 0) {


        return;
    }

    if (s->ti_cmd & CMD_DMA) {
        if (dmalen) {
            esp_do_dma(s);
        } else if (s->ti_size <= 0) {


            esp_dma_done(s);
            esp_lower_drq(s);
        }
    } else {
        esp_do_nodma(s);
    }
}
