follow_tcp_tap_listener(void *tapdata, packet_info *pinfo,
                      epan_dissect_t *edt _U_, const void *data)
{
    follow_record_t *follow_record;
    follow_info_t *follow_info = (follow_info_t *)tapdata;
    const tcp_follow_tap_data_t *follow_data = (const tcp_follow_tap_data_t *)data;
    gboolean is_server;
    guint32 sequence = follow_data->tcph->th_seq;
    guint32 length = follow_data->tcph->th_seglen;
    guint32 data_offset = 0;
    guint32 data_length = tvb_captured_length(follow_data->tvb);

    if (follow_data->tcph->th_flags & TH_SYN) {
        sequence++;
    }

    if (follow_info->client_port == 0) {
        follow_info->client_port = pinfo->srcport;
        copy_address(&follow_info->client_ip, &pinfo->src);
        follow_info->server_port = pinfo->destport;
        copy_address(&follow_info->server_ip, &pinfo->dst);
    }

    is_server = !(addresses_equal(&follow_info->client_ip, &pinfo->src) && follow_info->client_port == pinfo->srcport);


    if (follow_info->fragments[!is_server] != NULL) {
        while (check_follow_fragments(follow_info, !is_server, follow_data->tcph->th_ack, pinfo->fd->num));
    }


    if (follow_info->bytes_written[is_server] == 0 && follow_info->seq[is_server] == 0) {
        follow_info->seq[is_server] = sequence;
    }


    if (LT_SEQ(sequence, follow_info->seq[is_server])) {


        guint32 nextseq = sequence + length;
        if (GT_SEQ(nextseq, follow_info->seq[is_server])) {


            data_offset = follow_info->seq[is_server] - sequence;
            if (data_length <= data_offset) {
                data_length = 0;
            } else {
                data_length -= data_offset;
            }

            sequence = follow_info->seq[is_server];
            length = nextseq - follow_info->seq[is_server];
        }
    }


    if (data_length == 0 || LT_SEQ(sequence, follow_info->seq[is_server])) {
        return TAP_PACKET_DONT_REDRAW;
    }

    follow_record = g_new0(follow_record_t, 1);
    follow_record->is_server = is_server;
    follow_record->packet_num = pinfo->fd->num;
    follow_record->seq = sequence;
    follow_record->data = g_byte_array_append(g_byte_array_new(),
                                              tvb_get_ptr(follow_data->tvb, data_offset, data_length),
                                              data_length);

    if (EQ_SEQ(sequence, follow_info->seq[is_server])) {

        follow_info->seq[is_server] += length;
        follow_info->bytes_written[is_server] += follow_record->data->len;
        follow_info->payload = g_list_prepend(follow_info->payload, follow_record);


        while(check_follow_fragments(follow_info, is_server, 0, pinfo->fd->num));
    } else {

        follow_info->fragments[is_server] = g_list_append(follow_info->fragments[is_server], follow_record);
    }
    return TAP_PACKET_DONT_REDRAW;
}
