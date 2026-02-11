check_peer( n2n_edge_t * eee,
                 uint8_t from_supernode,
                 const n2n_mac_t mac,
                 const n2n_sock_t * peer )
{
    struct peer_info * scan = find_peer_by_mac( eee->known_peers, mac );

    if ( NULL == scan )
    {

        try_send_register( eee, from_supernode, mac, peer );
    }
    else
    {

        update_peer_address( eee, from_supernode, mac, peer, time(NULL) );
    }
}
