int av_read_packet(AVFormatContext *s, AVPacket *pkt) {
    int ret, i;
    AVStream *st;

    for (;;) {
        AVPacketList *pktl = s->raw_packet_buffer;

        if (pktl) {
            *pkt = pktl->pkt;
            st = s->streams[pkt->stream_index];
            if (st->codec->codec_id != CODEC_ID_PROBE ||
                !st->probe_packets || 
                s->raw_packet_buffer_remaining_size < pkt->size) {
                
                AVProbeData *pd = &st->probe_data;
                av_freep(&pd->buf);
                pd->buf_size = 0;
                s->raw_packet_buffer = pktl->next;
                s->raw_packet_buffer_remaining_size += pkt->size;
                av_free(pktl);
                return 0;
            }
        }

        av_init_packet(pkt);
        ret = s->iformat->read_packet(s, pkt);
        if (ret < 0) {
            if (!pktl || ret == AVERROR(EAGAIN))
                return ret;

            for (i = 0; i < s->nb_streams; i++)
                s->streams[i]->probe_packets = 0;
            continue;
        }

        st = s->streams[pkt->stream_index];
        switch (st->codec->codec_type) {
        case AVMEDIA_TYPE_VIDEO:
            if (s->video_codec_id)
                st->codec->codec_id = s->video_codec_id;
            break;
        case AVMEDIA_TYPE_AUDIO:
            if (s->audio_codec_id)
                st->codec->codec_id = s->audio_codec_id;
            break;
        case AVMEDIA_TYPE_SUBTITLE:
            if (s->subtitle_codec_id)
                st->codec->codec_id = s->subtitle_codec_id;
            break;
        }

        if (st->codec->codec_id == CODEC_ID_PROBE) {
            AVProbeData *pd = &st->probe_data;
            --st->probe_packets;
            pd->buf = av_realloc(pd->buf, pd->buf_size + pkt->size + AVPROBE_PADDING_SIZE);
            memcpy(pd->buf + pd->buf_size, pkt->data, pkt->size);
            pd->buf_size += pkt->size;
            memset(pd->buf + pd->buf_size, 0, AVPROBE_PADDING_SIZE);
            
            set_codec_from_probe_data(s, st, pd, st->probe_packets > 0 ? AVPROBE_SCORE_MAX / 4 : 0);
            
            if (st->codec->codec_id != CODEC_ID_PROBE) {
                pd->buf_size = 0;
                av_freep(&pd->buf);
            }
        }

        add_to_pktbuf(&s->raw_packet_buffer, pkt, &s->raw_packet_buffer_end);
        s->raw_packet_buffer_remaining_size -= pkt->size;
    }
}