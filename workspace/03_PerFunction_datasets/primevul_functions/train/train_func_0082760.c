void ide_atapi_cmd_reply_end(IDEState *s)
{
    int byte_count_limit, size, ret;
    while (s->packet_transfer_size > 0) {
        trace_ide_atapi_cmd_reply_end(s, s->packet_transfer_size,
                                      s->elementary_transfer_size,
                                      s->io_buffer_index);


        if (s->lba != -1 && s->io_buffer_index >= s->cd_sector_size) {
            if (!s->elementary_transfer_size) {
                ret = cd_read_sector(s);
                if (ret < 0) {
                    ide_atapi_io_error(s, ret);
                }
                return;
            } else {


                ret = cd_read_sector_sync(s);
                if (ret < 0) {
                    ide_atapi_io_error(s, ret);
                    return;
                }
            }
        }
        if (s->elementary_transfer_size > 0) {


            size = s->cd_sector_size - s->io_buffer_index;
            if (size > s->elementary_transfer_size)
                size = s->elementary_transfer_size;
        } else {

            s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO;
            ide_set_irq(s->bus);
            byte_count_limit = atapi_byte_count_limit(s);
            trace_ide_atapi_cmd_reply_end_bcl(s, byte_count_limit);
            size = s->packet_transfer_size;
            if (size > byte_count_limit) {

                if (byte_count_limit & 1)
                    byte_count_limit--;
                size = byte_count_limit;
            }
            s->lcyl = size;
            s->hcyl = size >> 8;
            s->elementary_transfer_size = size;

            if (s->lba != -1) {
                if (size > (s->cd_sector_size - s->io_buffer_index))
                    size = (s->cd_sector_size - s->io_buffer_index);
            }
            trace_ide_atapi_cmd_reply_end_new(s, s->status);
        }
        s->packet_transfer_size -= size;
        s->elementary_transfer_size -= size;
        s->io_buffer_index += size;


        if (!ide_transfer_start_norecurse(s,
                                          s->io_buffer + s->io_buffer_index - size,
                                          size, ide_atapi_cmd_reply_end)) {
            return;
        }
    }


    trace_ide_atapi_cmd_reply_end_eot(s, s->status);
    ide_atapi_cmd_ok(s);
    ide_set_irq(s->bus);
}
