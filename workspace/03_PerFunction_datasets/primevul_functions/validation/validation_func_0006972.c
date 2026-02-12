check_set_l4_port(struct ofpact_l4_port *a, struct ofpact_check_params *cp)
{
    const struct flow *flow = &cp->match->flow;
    if (!is_ip_any(flow)
        || flow->nw_frag & FLOW_NW_FRAG_LATER
        || (flow->nw_proto != IPPROTO_TCP &&
            flow->nw_proto != IPPROTO_UDP &&
            flow->nw_proto != IPPROTO_SCTP)) {
        inconsistent_match(&cp->usable_protocols);
    }


    a->flow_ip_proto = flow->nw_proto;

    return 0;
}
