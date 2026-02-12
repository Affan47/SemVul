static int gem_mac_address_filter(CadenceGEMState *s, const uint8_t *packet)
{
    uint8_t *gem_spaddr;
    int i, is_mc;


    if (s->regs[GEM_NWCFG] & GEM_NWCFG_PROMISC) {
        return GEM_RX_PROMISCUOUS_ACCEPT;
    }

    if (!memcmp(packet, broadcast_addr, 6)) {

        if (s->regs[GEM_NWCFG] & GEM_NWCFG_BCAST_REJ) {
            return GEM_RX_REJECT;
        }
        return GEM_RX_BROADCAST_ACCEPT;
    }


    is_mc = is_multicast_ether_addr(packet);
    if ((is_mc && (s->regs[GEM_NWCFG] & GEM_NWCFG_MCAST_HASH)) ||
        (!is_mc && (s->regs[GEM_NWCFG] & GEM_NWCFG_UCAST_HASH))) {
        uint64_t buckets;
        unsigned hash_index;

        hash_index = calc_mac_hash(packet);
        buckets = ((uint64_t)s->regs[GEM_HASHHI] << 32) | s->regs[GEM_HASHLO];
        if ((buckets >> hash_index) & 1) {
            return is_mc ? GEM_RX_MULTICAST_HASH_ACCEPT
                         : GEM_RX_UNICAST_HASH_ACCEPT;
        }
    }


    gem_spaddr = (uint8_t *)&(s->regs[GEM_SPADDR1LO]);
    for (i = 3; i >= 0; i--) {
        if (s->sar_active[i] && !memcmp(packet, gem_spaddr + 8 * i, 6)) {
            return GEM_RX_SAR_ACCEPT + i;
        }
    }


    return GEM_RX_REJECT;
}
