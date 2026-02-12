static void bdrv_mirror_top_child_perm(BlockDriverState *bs, BdrvChild *c,
                                       BdrvChildRole role,
                                       BlockReopenQueue *reopen_queue,
                                       uint64_t perm, uint64_t shared,
                                       uint64_t *nperm, uint64_t *nshared)
{
    MirrorBDSOpaque *s = bs->opaque;

    if (s->stop) {


        *nperm = 0;
        *nshared = BLK_PERM_ALL;
        return;
    }

    bdrv_default_perms(bs, c, role, reopen_queue,
                       perm, shared, nperm, nshared);

    if (s->is_commit) {


        *nperm &= ~BLK_PERM_CONSISTENT_READ;
        *nshared |= BLK_PERM_WRITE;
    }
}
