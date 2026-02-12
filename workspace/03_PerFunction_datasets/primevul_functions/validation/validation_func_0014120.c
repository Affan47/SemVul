dissect_tcpopt_snack(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
    struct tcp_analysis *tcpd=NULL;
    guint32 relative_hole_offset;
    guint32 relative_hole_size;
    guint16 base_mss = 0;
    guint32 ack;
    guint32 hole_start;
    guint32 hole_end;
    int     offset = 0;
    proto_item *hidden_item, *tf;
    proto_tree *field_tree;
    proto_item *length_item;

    tf = proto_tree_add_item(tree, proto_tcp_option_snack, tvb, offset, -1, ENC_NA);
    field_tree = proto_item_add_subtree(tf, ett_tcp_option_snack);

    proto_tree_add_item(field_tree, hf_tcp_option_kind, tvb,
                        offset, 1, ENC_BIG_ENDIAN);
    length_item = proto_tree_add_item(field_tree, hf_tcp_option_len, tvb,
                                      offset + 1, 1, ENC_BIG_ENDIAN);

    if (!tcp_option_len_check(length_item, pinfo, tvb_reported_length(tvb), TCPOLEN_SNACK))
        return tvb_captured_length(tvb);

    tcpd = get_tcp_conversation_data(NULL,pinfo);


    proto_tree_add_item_ret_uint(field_tree, hf_tcp_option_snack_offset,
                                      tvb, offset + 2, 2, ENC_BIG_ENDIAN, &relative_hole_offset);

    proto_tree_add_item_ret_uint(field_tree, hf_tcp_option_snack_size,
                                      tvb, offset + 4, 2, ENC_BIG_ENDIAN, &relative_hole_size);

    ack   = tvb_get_ntohl(tvb, 8);

    if (tcp_analyze_seq && tcp_relative_seq) {
        ack -= tcpd->rev->base_seq;
    }


    base_mss = tcpd->fwd->maxsizeacked;

    if (base_mss) {

        hole_start = ack + (base_mss * relative_hole_offset);
        hole_end   = hole_start + (base_mss * relative_hole_size);

        hidden_item = proto_tree_add_uint(field_tree, hf_tcp_option_snack_le,
                                          tvb, offset + 2, 2, hole_start);
        PROTO_ITEM_SET_HIDDEN(hidden_item);

        hidden_item = proto_tree_add_uint(field_tree, hf_tcp_option_snack_re,
                                          tvb, offset + 4, 2, hole_end);
        PROTO_ITEM_SET_HIDDEN(hidden_item);

        proto_tree_add_expert_format(field_tree, pinfo, &ei_tcp_option_snack_sequence, tvb, offset+2, 4,
                            "SNACK Sequence %u - %u%s", hole_start, hole_end, ((tcp_analyze_seq && tcp_relative_seq) ? " (relative)" : ""));

        tcp_info_append_uint(pinfo, "SNLE", hole_start);
        tcp_info_append_uint(pinfo, "SNRE", hole_end);
    }

    return tvb_captured_length(tvb);
}
