static inline bool nvme_addr_is_iomem(NvmeCtrl *n, hwaddr addr)
{
    hwaddr hi, lo;


    lo = n->bar0.addr;
    hi = lo + int128_get64(n->bar0.size);

    return addr >= lo && addr < hi;
}
