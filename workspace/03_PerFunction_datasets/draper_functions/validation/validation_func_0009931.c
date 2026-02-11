try_forward( n2n_sn_t * sss,
                        const n2n_common_t * cmn,
                        const n2n_mac_t dstMac,
                        const uint8_t * pktbuf,
                        size_t pktsize )
{
    struct peer_info *  scan;
    macstr_t            mac_buf;
    n2n_sock_str_t      sockbuf;

    scan = find_peer_by_mac( sss->edges, dstMac );

    if ( NULL != scan )
    {
        int data_sent_len;
        data_sent_len = sendto_sock( sss, &(scan->sock), pktbuf, pktsize );

        if ( data_sent_len == pktsize )
        {
            ++(sss->stats.fwd);
            traceEvent(TRACE_DEBUG, "unicast %lu to [%s] %s",
                       pktsize,
                       sock_to_cstr( sockbuf, &(scan->sock) ),
                       macaddr_str(mac_buf, scan->mac_addr));
        }
        else
        {
            ++(sss->stats.errors);
            traceEvent(TRACE_ERROR, "unicast %lu to [%s] %s FAILED (%d: %s)",
                       pktsize,
                       sock_to_cstr( sockbuf, &(scan->sock) ),
                       macaddr_str(mac_buf, scan->mac_addr),
                       errno, strerror(errno) );
        }
    }
    else
    {
        traceEvent( TRACE_DEBUG, "try_forward unknown MAC" );


    }

    return 0;
}
