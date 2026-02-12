static int sungem_check_rx_mac(SunGEMState *s, const uint8_t *mac, uint32_t crc)
{
    uint32_t rxcfg = s->macregs[MAC_RXCFG >> 2];
    uint32_t mac0, mac1, mac2;


    if (rxcfg & MAC_RXCFG_PROM) {
        return rx_match_promisc;
    }


    mac0 = (mac[4] << 8) | mac[5];
    mac1 = (mac[2] << 8) | mac[3];
    mac2 = (mac[0] << 8) | mac[1];

    trace_sungem_rx_mac_check(mac0, mac1, mac2);


    if (mac0 == 0xffff && mac1 == 0xffff && mac2 == 0xffff) {
        return rx_match_bcast;
    }


    if (mac[0] & 1) {
        trace_sungem_rx_mac_multicast();


        if (rxcfg & MAC_RXCFG_PGRP) {
            return rx_match_allmcast;
        }


        if (rxcfg & MAC_RXCFG_HFE) {
            uint32_t hash, idx;

            crc >>= 24;
            idx = (crc >> 2) & 0x3c;
            hash = s->macregs[(MAC_HASH0 + idx) >> 2];
            if (hash & (1 << (15 - (crc & 0xf)))) {
                return rx_match_mcast;
            }
        }
        return rx_no_match;
    }


    trace_sungem_rx_mac_compare(s->macregs[MAC_ADDR0 >> 2],
                                s->macregs[MAC_ADDR1 >> 2],
                                s->macregs[MAC_ADDR2 >> 2]);

    if (mac0 == s->macregs[MAC_ADDR0 >> 2] &&
        mac1 == s->macregs[MAC_ADDR1 >> 2] &&
        mac2 == s->macregs[MAC_ADDR2 >> 2]) {
        return rx_match_mac;
    }


    if (mac0 == s->macregs[MAC_ADDR3 >> 2] &&
        mac1 == s->macregs[MAC_ADDR4 >> 2] &&
        mac2 == s->macregs[MAC_ADDR5 >> 2]) {
        return rx_match_altmac;
    }

    return rx_no_match;
}
