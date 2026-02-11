print_ofchann_htbl(void)
{
    GHashTableIter ofch_iter;
    cc_ofchannel_key_t *ch_key = NULL;
    cc_ofchannel_info_t *ch_info = NULL;
    int n;
    g_hash_table_iter_init(&ofch_iter, cc_of_global.ofchannel_htbl);

    n = g_hash_table_size(cc_of_global.ofchannel_htbl);
    CC_LOG_DEBUG("Printing ofchannel Hash Table with %d entries",n);

    if (n) {
        while (g_hash_table_iter_next(&ofch_iter,
                                      (gpointer *)&ch_key,
                                      (gpointer *)&ch_info)) {
            CC_LOG_DEBUG("key: dp id: %lu "
                        "key: aux id: %hu "
                        "info: socket: %d",
                        ch_key->dp_id,
                        ch_key->aux_id,
                        ch_info->rw_sockfd);
        }
    }
}
