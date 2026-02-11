handle_getdata(struct ntb_network *nw,
               struct ntb_network_peer *peer,
               struct ntb_connection_getdata_event *event)
{
        struct ntb_network_inventory *inv;
        uint64_t i;

        for (i = 0; i < event->n_hashes; i++) {
                inv = ntb_hash_table_get(nw->inventory_hash,
                                         event->hashes + i *
                                         NTB_PROTO_HASH_LENGTH);
                if (inv && inv->state != NTB_NETWORK_INV_STATE_REJECTED) {
                        ntb_connection_send_blob(peer->connection,
                                                 inv->hash,
                                                 inv->blob);
                }
        }

        return true;
}
