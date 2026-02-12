static void gem_receive_updatestats(CadenceGEMState *s, const uint8_t *packet,
                                    unsigned bytes)
{
    uint64_t octets;


    octets = ((uint64_t)(s->regs[GEM_OCTRXLO]) << 32) |
             s->regs[GEM_OCTRXHI];
    octets += bytes;
    s->regs[GEM_OCTRXLO] = octets >> 32;
    s->regs[GEM_OCTRXHI] = octets;


    s->regs[GEM_RXCNT]++;


    if (!memcmp(packet, broadcast_addr, 6)) {
        s->regs[GEM_RXBROADCNT]++;
    }


    if (packet[0] == 0x01) {
        s->regs[GEM_RXMULTICNT]++;
    }

    if (bytes <= 64) {
        s->regs[GEM_RX64CNT]++;
    } else if (bytes <= 127) {
        s->regs[GEM_RX65CNT]++;
    } else if (bytes <= 255) {
        s->regs[GEM_RX128CNT]++;
    } else if (bytes <= 511) {
        s->regs[GEM_RX256CNT]++;
    } else if (bytes <= 1023) {
        s->regs[GEM_RX512CNT]++;
    } else if (bytes <= 1518) {
        s->regs[GEM_RX1024CNT]++;
    } else {
        s->regs[GEM_RX1519CNT]++;
    }
}
