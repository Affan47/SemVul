static int select_cur_seq_no(HLSContext *c, struct playlist *pls)
{
    int seq_no;

    if (!pls->finished && !c->first_packet &&
        av_gettime() - pls->last_load_time >= default_reload_interval(pls))

        parse_playlist(c, pls->url, pls, NULL);


    if (pls->finished && c->cur_timestamp != AV_NOPTS_VALUE) {
        find_timestamp_in_playlist(c, pls, c->cur_timestamp, &seq_no);
        return seq_no;
    }

    if (!pls->finished) {
        if (!c->first_packet &&
            c->cur_seq_no >= pls->start_seq_no &&
            c->cur_seq_no < pls->start_seq_no + pls->n_segments)


            return c->cur_seq_no;


        if (pls->n_segments > 3)
            return pls->start_seq_no + pls->n_segments - 3;
    }


    return pls->start_seq_no;
}
