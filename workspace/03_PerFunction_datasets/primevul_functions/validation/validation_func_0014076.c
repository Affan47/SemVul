dissect_tcp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
    guint8  th_off_x2;
    guint16 th_sum;
    guint32 th_urp;
    proto_tree *tcp_tree = NULL, *field_tree = NULL;
    proto_item *ti = NULL, *tf, *hidden_item;
    proto_item *options_item;
    proto_tree *options_tree;
    int        offset = 0;
    const char *flags_str, *flags_str_first_letter;
    guint      optlen;
    guint32    nxtseq = 0;
    guint      reported_len;
    vec_t      cksum_vec[4];
    guint32    phdr[2];
    guint16    computed_cksum;
    guint16    real_window;
    guint      captured_length_remaining;
    gboolean   desegment_ok;
    struct tcpinfo tcpinfo;
    struct tcpheader *tcph;
    proto_item *tf_syn = NULL, *tf_fin = NULL, *tf_rst = NULL, *scaled_pi;
    conversation_t *conv=NULL, *other_conv;
    guint32 save_last_frame = 0;
    struct tcp_analysis *tcpd=NULL;
    struct tcp_per_packet_data_t *tcppd=NULL;
    proto_item *item;
    proto_tree *checksum_tree;
    gboolean    icmp_ip = FALSE;

    tcph = wmem_new0(wmem_packet_scope(), struct tcpheader);
    tcph->th_sport = tvb_get_ntohs(tvb, offset);
    tcph->th_dport = tvb_get_ntohs(tvb, offset + 2);
    copy_address_shallow(&tcph->ip_src, &pinfo->src);
    copy_address_shallow(&tcph->ip_dst, &pinfo->dst);

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "TCP");
    col_clear(pinfo->cinfo, COL_INFO);
    col_append_ports(pinfo->cinfo, COL_INFO, PT_TCP, tcph->th_sport, tcph->th_dport);

    if (tree) {
        ti = proto_tree_add_item(tree, proto_tcp, tvb, 0, -1, ENC_NA);
        if (tcp_summary_in_tree) {
            proto_item_append_text(ti, ", Src Port: %s, Dst Port: %s",
                    port_with_resolution_to_str(wmem_packet_scope(), PT_TCP, tcph->th_sport),
                    port_with_resolution_to_str(wmem_packet_scope(), PT_TCP, tcph->th_dport));
        }
        tcp_tree = proto_item_add_subtree(ti, ett_tcp);
        p_add_proto_data(pinfo->pool, pinfo, proto_tcp, pinfo->curr_layer_num, tcp_tree);

        proto_tree_add_item(tcp_tree, hf_tcp_srcport, tvb, offset, 2, ENC_BIG_ENDIAN);
        proto_tree_add_item(tcp_tree, hf_tcp_dstport, tvb, offset + 2, 2, ENC_BIG_ENDIAN);
        hidden_item = proto_tree_add_item(tcp_tree, hf_tcp_port, tvb, offset, 2, ENC_BIG_ENDIAN);
        PROTO_ITEM_SET_HIDDEN(hidden_item);
        hidden_item = proto_tree_add_item(tcp_tree, hf_tcp_port, tvb, offset + 2, 2, ENC_BIG_ENDIAN);
        PROTO_ITEM_SET_HIDDEN(hidden_item);


        {
            wmem_list_frame_t *frame;
            frame = wmem_list_frame_prev(wmem_list_tail(pinfo->layers));
            if (proto_ip == (gint) GPOINTER_TO_UINT(wmem_list_frame_data(frame))) {
                frame = wmem_list_frame_prev(frame);
                if (proto_icmp == (gint) GPOINTER_TO_UINT(wmem_list_frame_data(frame))) {
                    proto_tree_add_item(tcp_tree, hf_tcp_seq, tvb, offset + 4, 4, ENC_BIG_ENDIAN);
                    icmp_ip = TRUE;
                }
            }
        }
    }


    pinfo->ptype = PT_TCP;
    pinfo->srcport = tcph->th_sport;
    pinfo->destport = tcph->th_dport;

    p_add_proto_data(pinfo->pool, pinfo, hf_tcp_srcport, pinfo->curr_layer_num, GUINT_TO_POINTER(tcph->th_sport));
    p_add_proto_data(pinfo->pool, pinfo, hf_tcp_dstport, pinfo->curr_layer_num, GUINT_TO_POINTER(tcph->th_dport));

    tcph->th_rawseq = tvb_get_ntohl(tvb, offset + 4);
    tcph->th_seq = tcph->th_rawseq;
    tcph->th_ack = tvb_get_ntohl(tvb, offset + 8);
    th_off_x2 = tvb_get_guint8(tvb, offset + 12);
    tcpinfo.flags = tcph->th_flags = tvb_get_ntohs(tvb, offset + 12) & TH_MASK;
    tcph->th_win = tvb_get_ntohs(tvb, offset + 14);
    real_window = tcph->th_win;
    tcph->th_hlen = hi_nibble(th_off_x2) * 4;


    if((conv = find_conversation_pinfo(pinfo, 0)) != NULL) {

        if (pinfo->num > conv->last_frame) {
            save_last_frame = conv->last_frame;
            conv->last_frame = pinfo->num;
        }
    }
    else {
        conv = conversation_new(pinfo->num, &pinfo->src,
                     &pinfo->dst, ENDPOINT_TCP,
                     pinfo->srcport, pinfo->destport, 0);
    }
    tcpd=get_tcp_conversation_data(conv,pinfo);


    if(tcpd && ((tcph->th_flags&(TH_SYN|TH_ACK))==TH_SYN) &&
       (tcpd->fwd->static_flags & TCP_S_BASE_SEQ_SET) &&
       (tcph->th_seq!=tcpd->fwd->base_seq) ) {
        if (!(pinfo->fd->visited)) {

            if (save_last_frame > 0)
                conv->last_frame = save_last_frame;

            conv=conversation_new(pinfo->num, &pinfo->src, &pinfo->dst, ENDPOINT_TCP, pinfo->srcport, pinfo->destport, 0);
            tcpd=get_tcp_conversation_data(conv,pinfo);
        }
        if(!tcpd->ta)
            tcp_analyze_get_acked_struct(pinfo->num, tcph->th_seq, tcph->th_ack, TRUE, tcpd);
        tcpd->ta->flags|=TCP_A_REUSED_PORTS;
    }


    if(tcpd && ((tcph->th_flags&(TH_SYN|TH_ACK))==(TH_SYN|TH_ACK)) &&
       (tcpd->fwd->static_flags & TCP_S_BASE_SEQ_SET) &&
       (tcph->th_seq!=tcpd->fwd->base_seq) ) {
        if (!(pinfo->fd->visited)) {

            if (save_last_frame > 0)
                conv->last_frame = save_last_frame;
        }

        other_conv = find_conversation(pinfo->num, &pinfo->dst, &pinfo->src, ENDPOINT_TCP, pinfo->destport, pinfo->srcport, 0);
        if (other_conv != NULL)
        {
            conv = other_conv;
            tcpd=get_tcp_conversation_data(conv,pinfo);
        }

        if(!tcpd->ta)
            tcp_analyze_get_acked_struct(pinfo->num, tcph->th_seq, tcph->th_ack, TRUE, tcpd);
        tcpd->ta->flags|=TCP_A_REUSED_PORTS;
    }

    if (tcpd) {
        item = proto_tree_add_uint(tcp_tree, hf_tcp_stream, tvb, offset, 0, tcpd->stream);
        PROTO_ITEM_SET_GENERATED(item);


        tcph->th_stream = tcpd->stream;
    }


    if (tcp_calculate_ts) {
        tcppd = (struct tcp_per_packet_data_t *)p_get_proto_data(wmem_file_scope(), pinfo, proto_tcp, pinfo->curr_layer_num);


        if (!(pinfo->fd->visited))
            tcp_calculate_timestamps(pinfo, tcpd, tcppd);
    }


    reported_len = tvb_reported_length(tvb);

    if (!pinfo->fragmented && !pinfo->flags.in_error_pkt) {
        if (reported_len < tcph->th_hlen) {
            proto_tree_add_expert_format(tcp_tree, pinfo, &ei_tcp_short_segment, tvb, offset, 0,
                                     "Short segment. Segment/fragment does not contain a full TCP header"
                                     " (might be NMAP or someone else deliberately sending unusual packets)");
            tcph->th_have_seglen = FALSE;
        } else {
            proto_item *pi;


            tcph->th_seglen = reported_len - tcph->th_hlen;
            tcph->th_have_seglen = TRUE;

            pi = proto_tree_add_uint(ti, hf_tcp_len, tvb, offset+12, 1, tcph->th_seglen);
            PROTO_ITEM_SET_GENERATED(pi);


            if(tcp_analyze_seq) {
                if(!(pinfo->fd->visited)) {
                    tcp_analyze_sequence_number(pinfo, tcph->th_seq, tcph->th_ack, tcph->th_seglen, tcph->th_flags, tcph->th_win, tcpd);
                }
                if(tcpd && tcp_relative_seq) {
                    (tcph->th_seq) -= tcpd->fwd->base_seq;
                    if (tcph->th_flags & TH_ACK) {
                        (tcph->th_ack) -= tcpd->rev->base_seq;
                    }
                }
            }


            if (!(tcph->th_flags&TH_SYN)) {
                if (tcpd && (tcpd->fwd->win_scale>=0)) {
                    (tcph->th_win)<<=tcpd->fwd->win_scale;
                }
                else {

                    if (tcp_default_window_scaling>=0) {
                        (tcph->th_win)<<=tcp_default_window_scaling;
                    }
                }
            }


            nxtseq = tcph->th_seq + tcph->th_seglen;
            if ((tcph->th_flags&(TH_SYN|TH_FIN)) && (tcph->th_seglen > 0)) {
                nxtseq += 1;
            }
        }
    } else
        tcph->th_have_seglen = FALSE;

    flags_str = tcp_flags_to_str(wmem_packet_scope(), tcph);
    flags_str_first_letter = tcp_flags_to_str_first_letter(tcph);

    col_append_lstr(pinfo->cinfo, COL_INFO,
        " [", flags_str, "]",
        COL_ADD_LSTR_TERMINATOR);
    tcp_info_append_uint(pinfo, "Seq", tcph->th_seq);
    if (tcph->th_flags&TH_ACK)
        tcp_info_append_uint(pinfo, "Ack", tcph->th_ack);

    tcp_info_append_uint(pinfo, "Win", tcph->th_win);

    if (tcp_summary_in_tree) {
        proto_item_append_text(ti, ", Seq: %u", tcph->th_seq);
    }

    if (!icmp_ip) {
        if(tcp_relative_seq && tcp_analyze_seq) {
            proto_tree_add_uint_format_value(tcp_tree, hf_tcp_seq, tvb, offset + 4, 4, tcph->th_seq, "%u    (relative sequence number)", tcph->th_seq);
        } else {
            proto_tree_add_uint(tcp_tree, hf_tcp_seq, tvb, offset + 4, 4, tcph->th_seq);
        }
    }

    if (tcph->th_hlen < TCPH_MIN_LEN) {


        col_append_fstr(pinfo->cinfo, COL_INFO, ", bogus TCP header length (%u, must be at least %u)",
                        tcph->th_hlen, TCPH_MIN_LEN);
        if (tree) {
            tf = proto_tree_add_uint_bits_format_value(tcp_tree, hf_tcp_hdr_len, tvb, (offset + 12) << 3, 4, tcph->th_hlen,
                                                       "%u bytes (%u)", tcph->th_hlen, tcph->th_hlen >> 2);
            expert_add_info_format(pinfo, tf, &ei_tcp_bogus_header_length,
                                   "Bogus TCP header length (%u, must be at least %u)", tcph->th_hlen, TCPH_MIN_LEN);
        }
        return offset+12;
    }

    if (tcp_summary_in_tree) {
        if(tcph->th_flags&TH_ACK) {
            proto_item_append_text(ti, ", Ack: %u", tcph->th_ack);
        }
        if (tcph->th_have_seglen)
            proto_item_append_text(ti, ", Len: %u", tcph->th_seglen);
    }
    proto_item_set_len(ti, tcph->th_hlen);
    if (tcph->th_have_seglen) {
        if(tcp_relative_seq && tcp_analyze_seq) {
            tf=proto_tree_add_uint_format_value(tcp_tree, hf_tcp_nxtseq, tvb, offset, 0, nxtseq, "%u    (relative sequence number)", nxtseq);
        } else {
            tf=proto_tree_add_uint(tcp_tree, hf_tcp_nxtseq, tvb, offset, 0, nxtseq);
        }
        PROTO_ITEM_SET_GENERATED(tf);
    }

    tf = proto_tree_add_uint(tcp_tree, hf_tcp_ack, tvb, offset + 8, 4, tcph->th_ack);
    if (tcph->th_flags & TH_ACK) {
        if (tcp_relative_seq && tcp_analyze_seq) {
            proto_item_append_text(tf, "    (relative ack number)");
        }
    } else {

        if (tvb_get_ntohl(tvb, offset+8) != 0) {
            expert_add_info(pinfo, tf, &ei_tcp_ack_nonzero);
        }
    }

    if (tree) {

        proto_tree_add_uint_bits_format_value(tcp_tree, hf_tcp_hdr_len, tvb, (offset + 12) << 3, 4, tcph->th_hlen,
            "%u bytes (%u)", tcph->th_hlen, tcph->th_hlen>>2);
        tf = proto_tree_add_uint_format(tcp_tree, hf_tcp_flags, tvb, offset + 12, 2,
                                        tcph->th_flags, "Flags: 0x%03x (%s)", tcph->th_flags, flags_str);
        field_tree = proto_item_add_subtree(tf, ett_tcp_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_res, tvb, offset + 12, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_ns, tvb, offset + 12, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_cwr, tvb, offset + 13, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_ecn, tvb, offset + 13, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_urg, tvb, offset + 13, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_ack, tvb, offset + 13, 1, tcph->th_flags);
        proto_tree_add_boolean(field_tree, hf_tcp_flags_push, tvb, offset + 13, 1, tcph->th_flags);
        tf_rst = proto_tree_add_boolean(field_tree, hf_tcp_flags_reset, tvb, offset + 13, 1, tcph->th_flags);
        tf_syn = proto_tree_add_boolean(field_tree, hf_tcp_flags_syn, tvb, offset + 13, 1, tcph->th_flags);
        tf_fin = proto_tree_add_boolean(field_tree, hf_tcp_flags_fin, tvb, offset + 13, 1, tcph->th_flags);

        tf = proto_tree_add_string(field_tree, hf_tcp_flags_str, tvb, offset + 12, 2, flags_str_first_letter);
        PROTO_ITEM_SET_GENERATED(tf);


        proto_tree_add_uint(tcp_tree, hf_tcp_window_size_value, tvb, offset + 14, 2, real_window);
        scaled_pi = proto_tree_add_uint(tcp_tree, hf_tcp_window_size, tvb, offset + 14, 2, tcph->th_win);
        PROTO_ITEM_SET_GENERATED(scaled_pi);

        if( !(tcph->th_flags&TH_SYN) && tcpd ) {
            switch (tcpd->fwd->win_scale) {

            case -1:
                {
                    gint16 win_scale = tcpd->fwd->win_scale;
                    gboolean override_with_pref = FALSE;


                    if (tcp_default_window_scaling != WindowScaling_NotKnown) {
                        win_scale = tcp_default_window_scaling;
                        override_with_pref = TRUE;
                    }

                    scaled_pi = proto_tree_add_int_format_value(tcp_tree, hf_tcp_window_size_scalefactor, tvb, offset + 14, 2,
                                                          win_scale, "%d (%s)",
                                                          win_scale,
                                                          (override_with_pref) ? "missing - taken from preference" : "unknown");
                    PROTO_ITEM_SET_GENERATED(scaled_pi);
                }
                break;

            case -2:
                scaled_pi = proto_tree_add_int_format_value(tcp_tree, hf_tcp_window_size_scalefactor, tvb, offset + 14, 2, tcpd->fwd->win_scale, "%d (no window scaling used)", tcpd->fwd->win_scale);
                PROTO_ITEM_SET_GENERATED(scaled_pi);
                break;

            default:
                scaled_pi = proto_tree_add_int_format_value(tcp_tree, hf_tcp_window_size_scalefactor, tvb, offset + 14, 2, 1<<tcpd->fwd->win_scale, "%d", 1<<tcpd->fwd->win_scale);
                PROTO_ITEM_SET_GENERATED(scaled_pi);
            }
        }
    }

    if(tcph->th_flags & TH_SYN) {
        if(tcph->th_flags & TH_ACK) {
           expert_add_info_format(pinfo, tf_syn, &ei_tcp_connection_sack,
                                  "Connection establish acknowledge (SYN+ACK): server port %u", tcph->th_sport);

           tcpd->server_port = tcph->th_sport;
        }
        else {
           expert_add_info_format(pinfo, tf_syn, &ei_tcp_connection_syn,
                                  "Connection establish request (SYN): server port %u", tcph->th_dport);

           tcpd->server_port = tcph->th_dport;
           tcpd->ts_mru_syn = pinfo->abs_ts;
        }

        if (tcp_desegment && tcp_reassemble_out_of_order && tcpd && !PINFO_FD_VISITED(pinfo)) {
            if (tcpd->fwd->maxnextseq == 0) {
                tcpd->fwd->maxnextseq = tcph->th_seq + 1;
            }
        }
    }
    if(tcph->th_flags & TH_FIN) {

        expert_add_info(pinfo, tf_fin, &ei_tcp_connection_fin);
    }
    if(tcph->th_flags & TH_RST)

        expert_add_info(pinfo, tf_rst, &ei_tcp_connection_rst);

    if(tcp_analyze_seq
            && (tcph->th_flags & (TH_SYN|TH_ACK)) == TH_ACK
            && !nstime_is_zero(&tcpd->ts_mru_syn)
            &&  nstime_is_zero(&tcpd->ts_first_rtt)) {


        nstime_delta(&(tcpd->ts_first_rtt), &(pinfo->abs_ts), &(tcpd->ts_mru_syn));
    }


    tcpinfo.seq = tcph->th_seq;
    tcpinfo.nxtseq = nxtseq;
    tcpinfo.lastackseq = tcph->th_ack;


    tcpinfo.is_reassembled = FALSE;


    pinfo->can_desegment = 0;
    th_sum = tvb_get_ntohs(tvb, offset + 16);
    if (!pinfo->fragmented && tvb_bytes_exist(tvb, 0, reported_len)) {


        if (tcp_check_checksum) {


            SET_CKSUM_VEC_PTR(cksum_vec[0], (const guint8 *)pinfo->src.data, pinfo->src.len);
            SET_CKSUM_VEC_PTR(cksum_vec[1], (const guint8 *)pinfo->dst.data, pinfo->dst.len);
            switch (pinfo->src.type) {

            case AT_IPv4:
                phdr[0] = g_htonl((IP_PROTO_TCP<<16) + reported_len);
                SET_CKSUM_VEC_PTR(cksum_vec[2], (const guint8 *)phdr, 4);
                break;

            case AT_IPv6:
                phdr[0] = g_htonl(reported_len);
                phdr[1] = g_htonl(IP_PROTO_TCP);
                SET_CKSUM_VEC_PTR(cksum_vec[2], (const guint8 *)phdr, 8);
                break;

            default:

                DISSECTOR_ASSERT_NOT_REACHED();
                break;
            }
            SET_CKSUM_VEC_TVB(cksum_vec[3], tvb, offset, reported_len);
            computed_cksum = in_cksum(cksum_vec, 4);
            if (computed_cksum == 0 && th_sum == 0xffff) {
                item = proto_tree_add_uint_format_value(tcp_tree, hf_tcp_checksum, tvb,
                                                  offset + 16, 2, th_sum,
                                                  "0x%04x [should be 0x0000 (see RFC 1624)]", th_sum);

                checksum_tree = proto_item_add_subtree(item, ett_tcp_checksum);
                item = proto_tree_add_uint(checksum_tree, hf_tcp_checksum_calculated, tvb,
                                              offset + 16, 2, 0x0000);
                PROTO_ITEM_SET_GENERATED(item);

                item = proto_tree_add_uint(checksum_tree, hf_tcp_checksum_status, tvb,
                                              offset + 16, 0, PROTO_CHECKSUM_E_BAD);
                PROTO_ITEM_SET_GENERATED(item);
                expert_add_info(pinfo, item, &ei_tcp_checksum_ffff);

                col_append_str(pinfo->cinfo, COL_INFO, " [TCP CHECKSUM 0xFFFF]");


                desegment_ok = TRUE;
            } else {
                proto_item* calc_item;
                item = proto_tree_add_checksum(tcp_tree, tvb, offset+16, hf_tcp_checksum, hf_tcp_checksum_status, &ei_tcp_checksum_bad, pinfo, computed_cksum,
                                               ENC_BIG_ENDIAN, PROTO_CHECKSUM_VERIFY|PROTO_CHECKSUM_IN_CKSUM);

                calc_item = proto_tree_add_uint(tcp_tree, hf_tcp_checksum_calculated, tvb,
                                              offset + 16, 2, in_cksum_shouldbe(th_sum, computed_cksum));
                PROTO_ITEM_SET_GENERATED(calc_item);


                if (computed_cksum == 0) {
                    desegment_ok = TRUE;
                } else {
                    proto_item_append_text(item, "(maybe caused by \"TCP checksum offload\"?)");


                    desegment_ok = FALSE;
                    pinfo->noreassembly_reason = " [incorrect TCP checksum]";
                    col_append_str(pinfo->cinfo, COL_INFO, " [TCP CHECKSUM INCORRECT]");
                }
            }
        } else {
            proto_tree_add_checksum(tcp_tree, tvb, offset+16, hf_tcp_checksum, hf_tcp_checksum_status, &ei_tcp_checksum_bad, pinfo, 0,
                                    ENC_BIG_ENDIAN, PROTO_CHECKSUM_NO_FLAGS);


            desegment_ok = TRUE;
        }
    } else {

        proto_tree_add_checksum(tcp_tree, tvb, offset+16, hf_tcp_checksum, hf_tcp_checksum_status, &ei_tcp_checksum_bad, pinfo, 0,
                                    ENC_BIG_ENDIAN, PROTO_CHECKSUM_NO_FLAGS);


        desegment_ok = FALSE;
    }

    if (desegment_ok) {

        if (tcp_desegment) {

            if (!pinfo->flags.in_error_pkt) {


                pinfo->can_desegment = 2;
            }
        }
    }

    item = proto_tree_add_item_ret_uint(tcp_tree, hf_tcp_urgent_pointer, tvb, offset + 18, 2, ENC_BIG_ENDIAN, &th_urp);

    if (IS_TH_URG(tcph->th_flags)) {


        tcpinfo.urgent_pointer = (guint16)th_urp;
        tcp_info_append_uint(pinfo, "Urg", th_urp);
    } else {
         if (th_urp) {

            expert_add_info(pinfo, item, &ei_tcp_urgent_pointer_non_zero);
         }
    }

    if (tcph->th_have_seglen)
        tcp_info_append_uint(pinfo, "Len", tcph->th_seglen);


    optlen = tcph->th_hlen - TCPH_MIN_LEN;
    options_item = NULL;
    options_tree = NULL;
    if (optlen != 0) {
        guint bc = (guint)tvb_captured_length_remaining(tvb, offset + 20);

        if (tcp_tree != NULL) {
            options_item = proto_tree_add_item(tcp_tree, hf_tcp_options, tvb, offset + 20,
                                               bc < optlen ? bc : optlen, ENC_NA);
            proto_item_set_text(options_item, "Options: (%u bytes)", optlen);
            options_tree = proto_item_add_subtree(options_item, ett_tcp_options);
        }
    }

    tcph->num_sack_ranges = 0;


    if(tcp_analyze_seq) {
        guint32 use_seq = tcph->th_seq;
        guint32 use_ack = tcph->th_ack;

        if (tcp_relative_seq) {
            use_seq += tcpd->fwd->base_seq;
            if (tcph->th_flags & TH_ACK) {
                use_ack += tcpd->rev->base_seq;
            }
        }
        tcp_print_sequence_number_analysis(pinfo, tvb, tcp_tree, tcpd, use_seq, use_ack);
    }


    if(tcp_calculate_ts) {
        tcp_print_timestamps(pinfo, tvb, tcp_tree, tcpd, tcppd);
    }


    if (optlen) {
        rvbd_option_data* option_data;

        tcp_dissect_options(tvb, offset + 20, optlen,
                               TCPOPT_EOL, pinfo, options_tree,
                               options_item, tcph);


        option_data = (rvbd_option_data*)p_get_proto_data(pinfo->pool, pinfo, proto_tcp_option_rvbd_probe, pinfo->curr_layer_num);
        if (option_data != NULL)
        {
            if (option_data->valid)
            {

                col_prepend_fstr(pinfo->cinfo, COL_INFO, "S%s, ",
                                     option_data->type == PROBE_TRACE ? "#" :
                                     (option_data->probe_flags & RVBD_FLAGS_PROBE_NCFE) ? "+*" : "+");
            }
        }

    }

    if(!pinfo->fd->visited) {
        if((tcph->th_flags & TH_SYN)==TH_SYN) {


            verify_tcp_window_scaling((tcph->th_flags&TH_ACK)==TH_ACK,tcpd);
        }

        if((tcph->th_flags & (TH_SYN|TH_ACK))==(TH_SYN|TH_ACK)) {


            if(tcpd && ((tcpd->rev->scps_capable) || (tcpd->fwd->scps_capable))) {
                verify_scps(pinfo, tf_syn, tcpd);
            }

        }
    }

    if (tcph->th_mptcp) {

        if (tcp_analyze_mptcp) {
            mptcp_add_analysis_subtree(pinfo, tvb, tcp_tree, tcpd, tcpd->mptcp_analysis, tcph );
        }
    }


    offset += tcph->th_hlen;


    captured_length_remaining = tvb_captured_length_remaining(tvb, offset);

    if (tcph->th_have_seglen) {
        if(have_tap_listener(tcp_follow_tap)) {
            tcp_follow_tap_data_t* follow_data = wmem_new0(wmem_packet_scope(), tcp_follow_tap_data_t);

            follow_data->tvb = tvb_new_subset_remaining(tvb, offset);
            follow_data->tcph = tcph;
            follow_data->tcpd = tcpd;

            tap_queue_packet(tcp_follow_tap, pinfo, follow_data);
        }
    }

    tap_queue_packet(tcp_tap, pinfo, tcph);


    if(tcpd->mptcp_analysis) {
        tap_queue_packet(mptcp_tap, pinfo, tcpd);
    }


    if(tcph->th_have_seglen && tcpd && (tcph->th_flags & TH_FIN)
       && (tcpd->fwd->flags&TCP_FLOW_REASSEMBLE_UNTIL_FIN) ) {
        struct tcp_multisegment_pdu *msp;


        if (tcpd->fwd->fin == 0 || tcpd->fwd->fin == pinfo->num) {


            tcpd->fwd->fin = pinfo->num;
            msp=(struct tcp_multisegment_pdu *)wmem_tree_lookup32_le(tcpd->fwd->multisegment_pdus, tcph->th_seq-1);
            if(msp) {
                fragment_head *ipfd_head;

                ipfd_head = fragment_add(&tcp_reassembly_table, tvb, offset,
                                         pinfo, msp->first_frame, NULL,
                                         tcph->th_seq - msp->seq,
                                         tcph->th_seglen,
                                         FALSE );
                if(ipfd_head) {
                    tvbuff_t *next_tvb;


                    next_tvb = tvb_new_chain(tvb, ipfd_head->tvb_data);


                    add_new_data_source(pinfo, next_tvb, "Reassembled TCP");


                    print_tcp_fragment_tree(ipfd_head, tree, tcp_tree, pinfo, next_tvb);


                    pinfo->can_desegment = 0;

                    process_tcp_payload(next_tvb, 0, pinfo, tree, tcp_tree, tcph->th_sport, tcph->th_dport, tcph->th_seq,
                                        nxtseq, FALSE, tcpd, &tcpinfo);

                    return tvb_captured_length(tvb);
                }
            }
        } else {


            proto_tree_add_uint(tcp_tree, hf_tcp_fin_retransmission, tvb, 0, 0, tcpd->fwd->fin);
        }
    }

    if (tcp_display_process_info && tcpd && ((tcpd->fwd && tcpd->fwd->process_info && tcpd->fwd->process_info->command) ||
                 (tcpd->rev && tcpd->rev->process_info && tcpd->rev->process_info->command))) {
        field_tree = proto_tree_add_subtree(tcp_tree, tvb, offset, 0, ett_tcp_process_info, &ti, "Process Information");
        PROTO_ITEM_SET_GENERATED(ti);
        if (tcpd->fwd && tcpd->fwd->process_info && tcpd->fwd->process_info->command) {
            proto_tree_add_uint(field_tree, hf_tcp_proc_dst_uid, tvb, 0, 0, tcpd->fwd->process_info->process_uid);
            proto_tree_add_uint(field_tree, hf_tcp_proc_dst_pid, tvb, 0, 0, tcpd->fwd->process_info->process_pid);
            proto_tree_add_string(field_tree, hf_tcp_proc_dst_uname, tvb, 0, 0, tcpd->fwd->process_info->username);
            proto_tree_add_string(field_tree, hf_tcp_proc_dst_cmd, tvb, 0, 0, tcpd->fwd->process_info->command);
        }
        if (tcpd->rev && tcpd->rev->process_info && tcpd->rev->process_info->command) {
            proto_tree_add_uint(field_tree, hf_tcp_proc_src_uid, tvb, 0, 0, tcpd->rev->process_info->process_uid);
            proto_tree_add_uint(field_tree, hf_tcp_proc_src_pid, tvb, 0, 0, tcpd->rev->process_info->process_pid);
            proto_tree_add_string(field_tree, hf_tcp_proc_src_uname, tvb, 0, 0, tcpd->rev->process_info->username);
            proto_tree_add_string(field_tree, hf_tcp_proc_src_cmd, tvb, 0, 0, tcpd->rev->process_info->command);
        }
    }


    if (captured_length_remaining != 0) {
        if (tcph->th_flags & TH_RST) {


            proto_tree_add_item(tcp_tree, hf_tcp_reset_cause, tvb, offset, captured_length_remaining, ENC_NA|ENC_ASCII);
        } else {


            if ((tcph->th_flags&(TH_FIN|TH_SYN)) && (tcph->th_seglen > 0)) {
                nxtseq -= 1;
            }
            dissect_tcp_payload(tvb, pinfo, offset, tcph->th_seq, nxtseq,
                                tcph->th_sport, tcph->th_dport, tree, tcp_tree, tcpd, &tcpinfo);
        }
    }
    return tvb_captured_length(tvb);
}
