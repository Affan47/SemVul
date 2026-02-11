ff_rdt_parse_packet(RDTDemuxContext *s, AVPacket *pkt,
                    const uint8_t *buf, int len)
{
    int seq_no, flags = 0, stream_id, set_id, is_keyframe;
    uint32_t timestamp;
    int rv= 0;

    if (!s->parse_packet)
        return -1;

    if (!buf && s->prev_stream_id != -1) {

        timestamp= 0;
        rv= s->parse_packet(s->ic, s->dynamic_protocol_context,
                            s->streams[s->prev_stream_id],
                            pkt, &timestamp, NULL, 0, flags);
        return rv;
    }

    if (len < 12)
        return -1;
    rv = ff_rdt_parse_header(buf, len, &set_id, &seq_no, &stream_id, &is_keyframe, &timestamp);
    if (rv < 0)
        return rv;
    if (is_keyframe &&
        (set_id != s->prev_set_id || timestamp != s->prev_timestamp ||
         stream_id != s->prev_stream_id)) {
        flags |= RTP_FLAG_KEY;
        s->prev_set_id    = set_id;
        s->prev_timestamp = timestamp;
    }
    s->prev_stream_id = stream_id;
    buf += rv;
    len -= rv;

     if (s->prev_stream_id >= s->n_streams) {
         s->prev_stream_id = -1;
         return -1;
     }

    rv = s->parse_packet(s->ic, s->dynamic_protocol_context,
                         s->streams[s->prev_stream_id],
                         pkt, &timestamp, buf, len, flags);

    return rv;
}
