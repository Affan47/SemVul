is_openais_cluster(void)
{
    enum cluster_type_e type = get_cluster_type();

    if (type == pcmk_cluster_classic_ais) {
        return TRUE;
    } else if (type == pcmk_cluster_corosync) {
        return TRUE;
    } else if (type == pcmk_cluster_cman) {
        return TRUE;
    }
    return FALSE;
}
