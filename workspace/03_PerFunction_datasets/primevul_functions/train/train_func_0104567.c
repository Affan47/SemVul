static void bdrv_mirror_top_refresh_filename(BlockDriverState *bs)
{
    if (bs->backing == NULL) {


        return;
    }
    pstrcpy(bs->exact_filename, sizeof(bs->exact_filename),
            bs->backing->bs->filename);
}
