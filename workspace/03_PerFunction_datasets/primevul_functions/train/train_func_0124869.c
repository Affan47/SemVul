static int mode_sense_page(SCSIDiskState *s, int page, uint8_t **p_outbuf,
                           int page_control)
{
    static const int mode_sense_valid[0x3f] = {
        [MODE_PAGE_HD_GEOMETRY]            = (1 << TYPE_DISK),
        [MODE_PAGE_FLEXIBLE_DISK_GEOMETRY] = (1 << TYPE_DISK),
        [MODE_PAGE_CACHING]                = (1 << TYPE_DISK) | (1 << TYPE_ROM),
        [MODE_PAGE_R_W_ERROR]              = (1 << TYPE_DISK) | (1 << TYPE_ROM),
        [MODE_PAGE_AUDIO_CTL]              = (1 << TYPE_ROM),
        [MODE_PAGE_CAPABILITIES]           = (1 << TYPE_ROM),
    };

    uint8_t *p = *p_outbuf + 2;
    int length;

    assert(page < ARRAY_SIZE(mode_sense_valid));
    if ((mode_sense_valid[page] & (1 << s->qdev.type)) == 0) {
        return -1;
    }


    switch (page) {
    case MODE_PAGE_HD_GEOMETRY:
        length = 0x16;
        if (page_control == 1) {
            break;
        }

        p[0] = (s->qdev.conf.cyls >> 16) & 0xff;
        p[1] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[2] = s->qdev.conf.cyls & 0xff;
        p[3] = s->qdev.conf.heads & 0xff;

        p[4] = (s->qdev.conf.cyls >> 16) & 0xff;
        p[5] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[6] = s->qdev.conf.cyls & 0xff;

        p[7] = (s->qdev.conf.cyls >> 16) & 0xff;
        p[8] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[9] = s->qdev.conf.cyls & 0xff;

        p[10] = 0;
        p[11] = 200;

        p[12] = 0xff;
        p[13] =  0xff;
        p[14] = 0xff;

        p[18] = (5400 >> 8) & 0xff;
        p[19] = 5400 & 0xff;
        break;

    case MODE_PAGE_FLEXIBLE_DISK_GEOMETRY:
        length = 0x1e;
        if (page_control == 1) {
            break;
        }

        p[0] = 5000 >> 8;
        p[1] = 5000 & 0xff;

        p[2] = s->qdev.conf.heads & 0xff;
        p[3] = s->qdev.conf.secs & 0xff;
        p[4] = s->qdev.blocksize >> 8;
        p[6] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[7] = s->qdev.conf.cyls & 0xff;

        p[8] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[9] = s->qdev.conf.cyls & 0xff;

        p[10] = (s->qdev.conf.cyls >> 8) & 0xff;
        p[11] = s->qdev.conf.cyls & 0xff;

        p[12] = 0;
        p[13] = 1;

        p[14] = 1;

        p[15] = 0;
        p[16] = 1;

        p[17] = 1;

        p[18] = 1;

        p[26] = (5400 >> 8) & 0xff;
        p[27] = 5400 & 0xff;
        break;

    case MODE_PAGE_CACHING:
        length = 0x12;
        if (page_control == 1 ||
            blk_enable_write_cache(s->qdev.conf.blk)) {
            p[0] = 4;
        }
        break;

    case MODE_PAGE_R_W_ERROR:
        length = 10;
        if (page_control == 1) {
            break;
        }
        p[0] = 0x80;
        if (s->qdev.type == TYPE_ROM) {
            p[1] = 0x20;
        }
        break;

    case MODE_PAGE_AUDIO_CTL:
        length = 14;
        break;

    case MODE_PAGE_CAPABILITIES:
        length = 0x14;
        if (page_control == 1) {
            break;
        }

        p[0] = 0x3b;
        p[1] = 0;
        p[2] = 0x7f;

        p[3] = 0xff;


        p[4] = 0x2d | (s->tray_locked ? 2 : 0);

        p[5] = 0;

        p[6] = (50 * 176) >> 8;
        p[7] = (50 * 176) & 0xff;
        p[8] = 2 >> 8;
        p[9] = 2 & 0xff;
        p[10] = 2048 >> 8;
        p[11] = 2048 & 0xff;
        p[12] = (16 * 176) >> 8;
        p[13] = (16 * 176) & 0xff;
        p[16] = (16 * 176) >> 8;
        p[17] = (16 * 176) & 0xff;
        p[18] = (16 * 176) >> 8;
        p[19] = (16 * 176) & 0xff;
        break;

    default:
        return -1;
    }

    assert(length < 256);
    (*p_outbuf)[0] = page;
    (*p_outbuf)[1] = length;
    *p_outbuf += length + 2;
    return length + 2;
}
