destruct_cluster(Cluster_info *ci, Cluster *cl)
{
    List *li;

    for (li = cl->item_list; li != NULL; li = li->next) {
        Qmap_remove(ci->cluster_index, li->data);
    }
    list_free(cl->item_list);

    free(cl);
}
