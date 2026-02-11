av_link(ventry *ve, ventry *newve)
{
    int res;

    res = compare_mount(ve->mnt, newve->mnt);
    if(res == 0) {
        struct avfs *avfs = ve->mnt->avfs;

        AVFS_LOCK(avfs);
        res = avfs->link(ve, newve);
        AVFS_UNLOCK(avfs);
    }

    return res;
}
