static int nvme_block_status_all(NvmeNamespace *ns, uint64_t slba,
                                 uint32_t nlb, int flags)
{
    BlockDriverState *bs = blk_bs(ns->blkconf.blk);

    int64_t pnum = 0, bytes = nvme_l2b(ns, nlb);
    int64_t offset = nvme_l2b(ns, slba);
    int ret;


    do {
        bytes -= pnum;

        ret = bdrv_block_status(bs, offset, bytes, &pnum, NULL, NULL);
        if (ret < 0) {
            return ret;
        }


        trace_pci_nvme_block_status(offset, bytes, pnum, ret,
                                    !!(ret & BDRV_BLOCK_ZERO));

        if (!(ret & flags)) {
            return 1;
        }

        offset += pnum;
    } while (pnum != bytes);

    return 0;
}
