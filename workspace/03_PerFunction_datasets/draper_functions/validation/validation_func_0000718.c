iperf_udp_recv(struct iperf_stream *sp)
{
    int       r;
    int       size = sp->settings->blksize;
    uint32_t  sec, usec, pcount;
    double    transit = 0, d = 0;
    struct timeval sent_time, arrival_time;

    r = Nread(sp->socket, sp->buffer, size, Pudp);

    if (r < 0)
        return r;

    sp->result->bytes_received += r;
    sp->result->bytes_received_this_interval += r;

    memcpy(&sec, sp->buffer, sizeof(sec));
    memcpy(&usec, sp->buffer+4, sizeof(usec));
    memcpy(&pcount, sp->buffer+8, sizeof(pcount));
    sec = ntohl(sec);
    usec = ntohl(usec);
    pcount = ntohl(pcount);
    sent_time.tv_sec = sec;
    sent_time.tv_usec = usec;


    if (pcount >= sp->packet_count + 1) {
        if (pcount > sp->packet_count + 1) {
            sp->cnt_error += (pcount - 1) - sp->packet_count;
        }
        sp->packet_count = pcount;
    } else {
        sp->outoforder_packets++;
	iperf_err(sp->test, "OUT OF ORDER - incoming packet = %d and received packet = %d AND SP = %d", pcount, sp->packet_count, sp->socket);
    }


    gettimeofday(&arrival_time, NULL);

    transit = timeval_diff(&sent_time, &arrival_time);
    d = transit - sp->prev_transit;
    if (d < 0)
        d = -d;
    sp->prev_transit = transit;


    sp->jitter += (d - sp->jitter) / 16.0;

    return r;
}
