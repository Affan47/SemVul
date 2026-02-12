check_PUSH_MPLS(const struct ofpact_push_mpls *a,
                struct ofpact_check_params *cp)
{
    struct flow *flow = &cp->match->flow;

    if (flow->packet_type != htonl(PT_ETH)) {
        inconsistent_match(&cp->usable_protocols);
    }
    flow->dl_type = a->ethertype;


    flow->nw_proto = 0;

    return 0;
}
