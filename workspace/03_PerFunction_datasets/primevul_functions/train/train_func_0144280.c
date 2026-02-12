static int ide_dvd_read_structure(IDEState *s, int format,
                                  const uint8_t *packet, uint8_t *buf)
{
    switch (format) {
        case 0x0:
            {
                int layer = packet[6];
                uint64_t total_sectors;

                if (layer != 0)
                    return -ASC_INV_FIELD_IN_CMD_PACKET;

                total_sectors = s->nb_sectors >> 2;
                if (total_sectors == 0) {
                    return -ASC_MEDIUM_NOT_PRESENT;
                }

                buf[4] = 1;
                buf[5] = 0xf;
                buf[6] = 1;
                buf[7] = 0;


                cpu_to_ube32(buf + 8, 0);
                cpu_to_ube32(buf + 12, total_sectors - 1);
                cpu_to_ube32(buf + 16, total_sectors - 1);


                cpu_to_be16wu((uint16_t *)buf, 2048 + 2);


                return (2048 + 4);
            }

        case 0x01:
            buf[4] = 0;
            buf[5] = 0;


            cpu_to_be16wu((uint16_t *)buf, 4 + 2);


            return (4 + 4);

        case 0x03:
            return -ASC_INV_FIELD_IN_CMD_PACKET;

        case 0x04:

            cpu_to_be16wu((uint16_t *)buf, 2048 + 2);


            return (2048 + 4);

        case 0xff:


            buf[4] = 0x00;
            buf[5] = 0x40;
            cpu_to_be16wu((uint16_t *)(buf + 6), 2048 + 4);

            buf[8] = 0x01;
            buf[9] = 0x40;
            cpu_to_be16wu((uint16_t *)(buf + 10), 4 + 4);

            buf[12] = 0x03;
            buf[13] = 0x40;
            cpu_to_be16wu((uint16_t *)(buf + 14), 188 + 4);

            buf[16] = 0x04;
            buf[17] = 0x40;
            cpu_to_be16wu((uint16_t *)(buf + 18), 2048 + 4);


            cpu_to_be16wu((uint16_t *)buf, 16 + 2);


            return (16 + 4);

        default:
            return -ASC_INV_FIELD_IN_CMD_PACKET;
    }
}
