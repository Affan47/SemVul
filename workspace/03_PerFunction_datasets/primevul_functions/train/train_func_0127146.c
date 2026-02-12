ofproto_unixctl_trace_actions(struct unixctl_conn *conn, int argc,
                              const char *argv[], void *aux OVS_UNUSED)
{
    enum ofputil_protocol usable_protocols;
    struct ofproto_dpif *ofproto;
    bool enforce_consistency;
    struct ofpbuf ofpacts;
    struct dp_packet *packet;
    struct ds result;
    struct match match;
    uint16_t in_port;
    struct ovs_list next_ct_states = OVS_LIST_INITIALIZER(&next_ct_states);


    enum ofperr retval;
    char *error;

    packet = NULL;
    ds_init(&result);
    ofpbuf_init(&ofpacts, 0);


    struct ofpact_parse_params pp = {
        .port_map = NULL,
        .ofpacts = &ofpacts,
        .usable_protocols = &usable_protocols,
    };
    error = ofpacts_parse_actions(argv[--argc], &pp);
    if (error) {
        unixctl_command_reply_error(conn, error);
        free(error);
        goto exit;
    }

    error = parse_flow_and_packet(argc, argv, &ofproto, &match.flow, &packet,
                                  &next_ct_states, &enforce_consistency);
    if (error) {
        unixctl_command_reply_error(conn, error);
        free(error);
        goto exit;
    }
    match_wc_init(&match, &match.flow);


    in_port = ofp_to_u16(match.flow.in_port.ofp_port);
    if (in_port >= ofproto->up.max_ports && in_port < ofp_to_u16(OFPP_MAX)) {
        unixctl_command_reply_error(conn, "invalid in_port");
        goto exit;
    }

    struct ofpact_check_params cp = {
        .match = &match,
        .max_ports = u16_to_ofp(ofproto->up.max_ports),
        .table_id = 0,
        .n_tables = ofproto->up.n_tables,
    };
    retval = ofpacts_check_consistency(
        ofpacts.data, ofpacts.size,
        enforce_consistency ? usable_protocols : 0, &cp);
    if (!retval) {
        ovs_mutex_lock(&ofproto_mutex);
        retval = ofproto_check_ofpacts(&ofproto->up, ofpacts.data,
                                       ofpacts.size);
        ovs_mutex_unlock(&ofproto_mutex);
    }

    if (retval) {
        ds_clear(&result);
        ds_put_format(&result, "Bad actions: %s", ofperr_to_string(retval));
        unixctl_command_reply_error(conn, ds_cstr(&result));
        goto exit;
    }

    ofproto_trace(ofproto, &match.flow, packet,
                  ofpacts.data, ofpacts.size, &next_ct_states, &result);
    unixctl_command_reply(conn, ds_cstr(&result));

exit:
    ds_destroy(&result);
    dp_packet_delete(packet);
    ofpbuf_uninit(&ofpacts);
    free_ct_states(&next_ct_states);
}
