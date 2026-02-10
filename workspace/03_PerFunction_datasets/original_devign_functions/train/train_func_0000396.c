static void coroutine_fn wait_for_overlapping_requests(BlockDriverState *bs, int64_t sector_num, int nb_sectors) {
    BdrvTrackedRequest *req;
    int64_t cluster_sector_num;
    int cluster_nb_sectors;
    bool retry;
