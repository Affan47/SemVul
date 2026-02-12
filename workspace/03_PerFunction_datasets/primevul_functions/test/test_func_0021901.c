static ssize_t gem_receive(NetClientState *nc, const uint8_t *buf, size_t size)
{
    CadenceGEMState *s = qemu_get_nic_opaque(nc);
    unsigned   rxbufsize, bytes_to_copy;
    unsigned   rxbuf_offset;
    uint8_t   *rxbuf_ptr;
    bool first_desc = true;
    int maf;
    int q = 0;


    maf = gem_mac_address_filter(s, buf);
    if (maf == GEM_RX_REJECT) {
        return size;
    }


    if (s->regs[GEM_NWCFG] & GEM_NWCFG_LERR_DISC) {
        unsigned type_len;


        type_len = buf[12] << 8 | buf[13];

        if (type_len < 0x600) {
            if (size < type_len) {

                return -1;
            }
        }
    }


    rxbuf_offset = (s->regs[GEM_NWCFG] & GEM_NWCFG_BUFF_OFST_M) >>
                   GEM_NWCFG_BUFF_OFST_S;


    rxbufsize = ((s->regs[GEM_DMACFG] & GEM_DMACFG_RBUFSZ_M) >>
                 GEM_DMACFG_RBUFSZ_S) * GEM_DMACFG_RBUFSZ_MUL;
    bytes_to_copy = size;


    if (rxbufsize < GEM_DMACFG_RBUFSZ_MUL) {
        rxbufsize = GEM_DMACFG_RBUFSZ_MUL;
    }


    if (size < 60) {
        size = 60;
    }


    if (s->regs[GEM_NWCFG] & GEM_NWCFG_STRIP_FCS) {
        rxbuf_ptr = (void *)buf;
    } else {
        unsigned crc_val;

        if (size > MAX_FRAME_SIZE - sizeof(crc_val)) {
            size = MAX_FRAME_SIZE - sizeof(crc_val);
        }
        bytes_to_copy = size;


        memcpy(s->rx_packet, buf, size);
        memset(s->rx_packet + size, 0, MAX_FRAME_SIZE - size);
        rxbuf_ptr = s->rx_packet;
        crc_val = cpu_to_le32(crc32(0, s->rx_packet, MAX(size, 60)));
        memcpy(s->rx_packet + size, &crc_val, sizeof(crc_val));

        bytes_to_copy += 4;
        size += 4;
    }

    DB_PRINT("config bufsize: %u packet size: %zd\n", rxbufsize, size);


    q = get_queue_from_screen(s, rxbuf_ptr, rxbufsize);

    if (size > gem_get_max_buf_len(s, false)) {
        qemu_log_mask(LOG_GUEST_ERROR, "rx frame too long\n");
        gem_set_isr(s, q, GEM_INT_AMBA_ERR);
        return -1;
    }

    while (bytes_to_copy) {
        hwaddr desc_addr;


        if (!gem_can_receive(nc)) {
            return -1;
        }

        DB_PRINT("copy %" PRIu32 " bytes to 0x%" PRIx64 "\n",
                MIN(bytes_to_copy, rxbufsize),
                rx_desc_get_buffer(s, s->rx_desc[q]));


        address_space_write(&s->dma_as, rx_desc_get_buffer(s, s->rx_desc[q]) +
                                                                  rxbuf_offset,
                            MEMTXATTRS_UNSPECIFIED, rxbuf_ptr,
                            MIN(bytes_to_copy, rxbufsize));
        rxbuf_ptr += MIN(bytes_to_copy, rxbufsize);
        bytes_to_copy -= MIN(bytes_to_copy, rxbufsize);

        rx_desc_clear_control(s->rx_desc[q]);


        if (first_desc) {
            rx_desc_set_sof(s->rx_desc[q]);
            first_desc = false;
        }
        if (bytes_to_copy == 0) {
            rx_desc_set_eof(s->rx_desc[q]);
            rx_desc_set_length(s->rx_desc[q], size);
        }
        rx_desc_set_ownership(s->rx_desc[q]);

        switch (maf) {
        case GEM_RX_PROMISCUOUS_ACCEPT:
            break;
        case GEM_RX_BROADCAST_ACCEPT:
            rx_desc_set_broadcast(s->rx_desc[q]);
            break;
        case GEM_RX_UNICAST_HASH_ACCEPT:
            rx_desc_set_unicast_hash(s->rx_desc[q]);
            break;
        case GEM_RX_MULTICAST_HASH_ACCEPT:
            rx_desc_set_multicast_hash(s->rx_desc[q]);
            break;
        case GEM_RX_REJECT:
            abort();
        default:
            rx_desc_set_sar(s->rx_desc[q], maf);
        }


        desc_addr = gem_get_rx_desc_addr(s, q);
        address_space_write(&s->dma_as, desc_addr, MEMTXATTRS_UNSPECIFIED,
                            s->rx_desc[q],
                            sizeof(uint32_t) * gem_get_desc_len(s, true));


        if (rx_desc_get_wrap(s->rx_desc[q])) {
            DB_PRINT("wrapping RX descriptor list\n");
            s->rx_desc_addr[q] = gem_get_rx_queue_base_addr(s, q);
        } else {
            DB_PRINT("incrementing RX descriptor list\n");
            s->rx_desc_addr[q] += 4 * gem_get_desc_len(s, true);
        }

        gem_get_rx_desc(s, q);
    }


    gem_receive_updatestats(s, buf, size);

    s->regs[GEM_RXSTATUS] |= GEM_RXSTATUS_FRMRCVD;
    gem_set_isr(s, q, GEM_INT_RXCMPL);


    gem_update_int_status(s);

    return size;
}
