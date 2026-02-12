static void esp_do_dma(ESPState *s)
{
    uint32_t len, cmdlen;
    int to_device = ((s->rregs[ESP_RSTAT] & 7) == STAT_DO);
    uint8_t buf[ESP_CMDFIFO_SZ];

    len = esp_get_tc(s);
    if (s->do_cmd) {


        cmdlen = fifo8_num_used(&s->cmdfifo);
        trace_esp_do_dma(cmdlen, len);
        if (s->dma_memory_read) {
            s->dma_memory_read(s->dma_opaque, buf, len);
            fifo8_push_all(&s->cmdfifo, buf, len);
        } else {
            s->pdma_cb = do_dma_pdma_cb;
            esp_raise_drq(s);
            return;
        }
        trace_esp_handle_ti_cmd(cmdlen);
        s->ti_size = 0;
        if ((s->rregs[ESP_RSTAT] & 7) == STAT_CD) {

            if (s->cmdfifo_cdb_offset == fifo8_num_used(&s->cmdfifo)) {
                return;
            }


            s->do_cmd = 0;
            do_cmd(s);
        } else {


            s->cmdfifo_cdb_offset = fifo8_num_used(&s->cmdfifo);
            s->rregs[ESP_RSTAT] = STAT_TC | STAT_CD;
            s->rregs[ESP_RSEQ] = SEQ_CD;
            s->rregs[ESP_RINTR] |= INTR_BS;
            esp_raise_irq(s);
        }
        return;
    }
    if (!s->current_req) {
        return;
    }
    if (s->async_len == 0) {

        return;
    }
    if (len > s->async_len) {
        len = s->async_len;
    }
    if (to_device) {
        if (s->dma_memory_read) {
            s->dma_memory_read(s->dma_opaque, s->async_buf, len);
        } else {
            s->pdma_cb = do_dma_pdma_cb;
            esp_raise_drq(s);
            return;
        }
    } else {
        if (s->dma_memory_write) {
            s->dma_memory_write(s->dma_opaque, s->async_buf, len);
        } else {

            if (!fifo8_is_empty(&s->fifo)) {
                esp_set_tc(s, esp_get_tc(s) - fifo8_num_used(&s->fifo));
            }


            len = MIN(len, fifo8_num_free(&s->fifo));
            fifo8_push_all(&s->fifo, s->async_buf, len);
            s->async_buf += len;
            s->async_len -= len;
            s->ti_size -= len;


            if (len < esp_get_tc(s) && esp_get_tc(s) <= ESP_FIFO_SZ) {
                while (fifo8_num_used(&s->fifo) < ESP_FIFO_SZ) {
                    esp_fifo_push(&s->fifo, 0);
                    len++;
                }
            }

            esp_set_tc(s, esp_get_tc(s) - len);
            s->pdma_cb = do_dma_pdma_cb;
            esp_raise_drq(s);


            s->rregs[ESP_RSTAT] |= STAT_TC;
            return;
        }
    }
    esp_set_tc(s, esp_get_tc(s) - len);
    s->async_buf += len;
    s->async_len -= len;
    if (to_device) {
        s->ti_size += len;
    } else {
        s->ti_size -= len;
    }
    if (s->async_len == 0) {
        scsi_req_continue(s->current_req);


        if (to_device || esp_get_tc(s) != 0 || s->ti_size == 0) {
            return;
        }
    }


    esp_dma_done(s);
    esp_lower_drq(s);
}
