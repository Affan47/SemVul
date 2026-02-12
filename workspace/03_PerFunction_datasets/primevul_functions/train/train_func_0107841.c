static void ide_identify(IDEState *s)
{
    uint16_t *p;
    unsigned int oldsize;
    IDEDevice *dev = s->unit ? s->bus->slave : s->bus->master;

    if (s->identify_set) {
	memcpy(s->io_buffer, s->identify_data, sizeof(s->identify_data));
	return;
    }

    memset(s->io_buffer, 0, 512);
    p = (uint16_t *)s->io_buffer;
    put_le16(p + 0, 0x0040);
    put_le16(p + 1, s->cylinders);
    put_le16(p + 3, s->heads);
    put_le16(p + 4, 512 * s->sectors);
    put_le16(p + 5, 512);
    put_le16(p + 6, s->sectors);
    padstr((char *)(p + 10), s->drive_serial_str, 20);
    put_le16(p + 20, 3);
    put_le16(p + 21, 512);
    put_le16(p + 22, 4);
    padstr((char *)(p + 23), s->version, 8);
    padstr((char *)(p + 27), s->drive_model_str, 40);
#if MAX_MULT_SECTORS > 1
    put_le16(p + 47, 0x8000 | MAX_MULT_SECTORS);
#endif
    put_le16(p + 48, 1);
    put_le16(p + 49, (1 << 11) | (1 << 9) | (1 << 8));
    put_le16(p + 51, 0x200);
    put_le16(p + 52, 0x200);
    put_le16(p + 53, 1 | (1 << 1) | (1 << 2));
    put_le16(p + 54, s->cylinders);
    put_le16(p + 55, s->heads);
    put_le16(p + 56, s->sectors);
    oldsize = s->cylinders * s->heads * s->sectors;
    put_le16(p + 57, oldsize);
    put_le16(p + 58, oldsize >> 16);
    if (s->mult_sectors)
        put_le16(p + 59, 0x100 | s->mult_sectors);
    put_le16(p + 60, s->nb_sectors);
    put_le16(p + 61, s->nb_sectors >> 16);
    put_le16(p + 62, 0x07);
    put_le16(p + 63, 0x07);
    put_le16(p + 64, 0x03);
    put_le16(p + 65, 120);
    put_le16(p + 66, 120);
    put_le16(p + 67, 120);
    put_le16(p + 68, 120);
    if (dev && dev->conf.discard_granularity) {
        put_le16(p + 69, (1 << 14));
    }

    if (s->ncq_queues) {
        put_le16(p + 75, s->ncq_queues - 1);

        put_le16(p + 76, (1 << 8));
    }

    put_le16(p + 80, 0xf0);
    put_le16(p + 81, 0x16);

    put_le16(p + 82, (1 << 14) | (1 << 5) | 1);

    put_le16(p + 83, (1 << 14) | (1 << 13) | (1 <<12) | (1 << 10));

    if (s->wwn) {
        put_le16(p + 84, (1 << 14) | (1 << 8) | 0);
    } else {
        put_le16(p + 84, (1 << 14) | 0);
    }

    if (bdrv_enable_write_cache(s->bs))
         put_le16(p + 85, (1 << 14) | (1 << 5) | 1);
    else
         put_le16(p + 85, (1 << 14) | 1);

    put_le16(p + 86, (1 << 13) | (1 <<12) | (1 << 10));

    if (s->wwn) {
        put_le16(p + 87, (1 << 14) | (1 << 8) | 0);
    } else {
        put_le16(p + 87, (1 << 14) | 0);
    }
    put_le16(p + 88, 0x3f | (1 << 13));
    put_le16(p + 93, 1 | (1 << 14) | 0x2000);
    put_le16(p + 100, s->nb_sectors);
    put_le16(p + 101, s->nb_sectors >> 16);
    put_le16(p + 102, s->nb_sectors >> 32);
    put_le16(p + 103, s->nb_sectors >> 48);

    if (dev && dev->conf.physical_block_size)
        put_le16(p + 106, 0x6000 | get_physical_block_exp(&dev->conf));
    if (s->wwn) {

        put_le16(p + 108, s->wwn >> 48);
        put_le16(p + 109, s->wwn >> 32);
        put_le16(p + 110, s->wwn >> 16);
        put_le16(p + 111, s->wwn);
    }
    if (dev && dev->conf.discard_granularity) {
        put_le16(p + 169, 1);
    }

    memcpy(s->identify_data, p, sizeof(s->identify_data));
    s->identify_set = 1;
}
