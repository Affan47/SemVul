check_DECAP(const struct ofpact_decap *a OVS_UNUSED,
            struct ofpact_check_params *cp)
{
    struct flow *flow = &cp->match->flow;
    if (flow->packet_type == htonl(PT_ETH)) {

        flow->packet_type = PACKET_TYPE_BE(OFPHTN_ETHERTYPE,
                                           ntohs(flow->dl_type));
    } else {


        flow->packet_type = htonl(PT_UNKNOWN);
        flow->dl_type = OVS_BE16_MAX;
    }
    return 0;
}
