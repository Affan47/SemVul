tcpip_hostlist_packet(void *pit, packet_info *pinfo, epan_dissect_t *edt _U_, const void *vip)
{
    conv_hash_t *hash = (conv_hash_t*) pit;
    const struct tcpheader *tcphdr=(const struct tcpheader *)vip;


    add_hostlist_table_data(hash, &tcphdr->ip_src, tcphdr->th_sport, TRUE, 1, pinfo->fd->pkt_len, &tcp_host_dissector_info, ENDPOINT_TCP);
    add_hostlist_table_data(hash, &tcphdr->ip_dst, tcphdr->th_dport, FALSE, 1, pinfo->fd->pkt_len, &tcp_host_dissector_info, ENDPOINT_TCP);

    return TAP_PACKET_REDRAW;
}
