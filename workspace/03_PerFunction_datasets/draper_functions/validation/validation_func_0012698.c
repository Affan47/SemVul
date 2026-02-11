sort_peers(gconstpointer a, gconstpointer b)
{
    const st_query_result_t *peer_a = a;
    const st_query_result_t *peer_b = a;

    if (peer_a->devices > peer_b->devices) {
        return -1;
    } else if (peer_a->devices > peer_b->devices) {
        return 1;
    }
    return 0;
}
