static int scsi_disk_emulate_vpd_page(SCSIRequest *req, uint8_t *outbuf)
{
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, req->dev);
    uint8_t page_code = req->cmd.buf[2];
    int start, buflen = 0;

    outbuf[buflen++] = s->qdev.type & 0x1f;
    outbuf[buflen++] = page_code;
    outbuf[buflen++] = 0x00;
    outbuf[buflen++] = 0x00;
    start = buflen;

    switch (page_code) {
    case 0x00:
    {
        trace_scsi_disk_emulate_vpd_page_00(req->cmd.xfer);
        outbuf[buflen++] = 0x00;
        if (s->serial) {
            outbuf[buflen++] = 0x80;
        }
        outbuf[buflen++] = 0x83;
        if (s->qdev.type == TYPE_DISK) {
            outbuf[buflen++] = 0xb0;
            outbuf[buflen++] = 0xb1;
            outbuf[buflen++] = 0xb2;
        }
        break;
    }
    case 0x80:
    {
        int l;

        if (!s->serial) {
            trace_scsi_disk_emulate_vpd_page_80_not_supported();
            return -1;
        }

        l = strlen(s->serial);
        if (l > 36) {
            l = 36;
        }

        trace_scsi_disk_emulate_vpd_page_80(req->cmd.xfer);
        memcpy(outbuf + buflen, s->serial, l);
        buflen += l;
        break;
    }

    case 0x83:
    {
        int id_len = s->device_id ? MIN(strlen(s->device_id), 255 - 8) : 0;

        trace_scsi_disk_emulate_vpd_page_83(req->cmd.xfer);

        if (id_len) {
            outbuf[buflen++] = 0x2;
            outbuf[buflen++] = 0;
            outbuf[buflen++] = 0;
            outbuf[buflen++] = id_len;
            memcpy(outbuf + buflen, s->device_id, id_len);
            buflen += id_len;
        }

        if (s->qdev.wwn) {
            outbuf[buflen++] = 0x1;
            outbuf[buflen++] = 0x3;
            outbuf[buflen++] = 0;
            outbuf[buflen++] = 8;
            stq_be_p(&outbuf[buflen], s->qdev.wwn);
            buflen += 8;
        }

        if (s->qdev.port_wwn) {
            outbuf[buflen++] = 0x61;
            outbuf[buflen++] = 0x93;
            outbuf[buflen++] = 0;
            outbuf[buflen++] = 8;
            stq_be_p(&outbuf[buflen], s->qdev.port_wwn);
            buflen += 8;
        }

        if (s->port_index) {
            outbuf[buflen++] = 0x61;


            outbuf[buflen++] = 0x94;

            outbuf[buflen++] = 0;
            outbuf[buflen++] = 4;
            stw_be_p(&outbuf[buflen + 2], s->port_index);
            buflen += 4;
        }
        break;
    }
    case 0xb0:
    {
        SCSIBlockLimits bl = {};

        if (s->qdev.type == TYPE_ROM) {
            trace_scsi_disk_emulate_vpd_page_b0_not_supported();
            return -1;
        }
        bl.wsnz = 1;
        bl.unmap_sectors =
            s->qdev.conf.discard_granularity / s->qdev.blocksize;
        bl.min_io_size =
            s->qdev.conf.min_io_size / s->qdev.blocksize;
        bl.opt_io_size =
            s->qdev.conf.opt_io_size / s->qdev.blocksize;
        bl.max_unmap_sectors =
            s->max_unmap_size / s->qdev.blocksize;
        bl.max_io_sectors =
            s->max_io_size / s->qdev.blocksize;

        bl.max_unmap_descr = 255;

        if (s->qdev.type == TYPE_DISK) {
            int max_transfer_blk = blk_get_max_transfer(s->qdev.conf.blk);
            int max_io_sectors_blk =
                max_transfer_blk / s->qdev.blocksize;

            bl.max_io_sectors =
                MIN_NON_ZERO(max_io_sectors_blk, bl.max_io_sectors);
        }
        buflen += scsi_emulate_block_limits(outbuf + buflen, &bl);
        break;
    }
    case 0xb1:
    {
        buflen = 0x40;
        outbuf[4] = (s->rotation_rate >> 8) & 0xff;
        outbuf[5] = s->rotation_rate & 0xff;
        outbuf[6] = 0;
        outbuf[7] = 0;
        outbuf[8] = 0;
        break;
    }
    case 0xb2:
    {
        buflen = 8;
        outbuf[4] = 0;
        outbuf[5] = 0xe0;
        outbuf[6] = s->qdev.conf.discard_granularity ? 2 : 1;
        outbuf[7] = 0;
        break;
    }
    default:
        return -1;
    }

    assert(buflen - start <= 255);
    outbuf[start - 1] = buflen - start;
    return buflen;
}
