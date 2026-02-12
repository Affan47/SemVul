IOMMUTLBEntry address_space_get_iotlb_entry(AddressSpace *as, hwaddr addr,
                                            bool is_write)
{
    MemoryRegionSection section;
    hwaddr xlat, plen;


    plen = (hwaddr)-1;


    section = address_space_do_translate(as, addr, &xlat, &plen,
                                         is_write, false);


    if (section.mr == &io_mem_unassigned) {
        goto iotlb_fail;
    }


    xlat += section.offset_within_address_space -
        section.offset_within_region;

    if (plen == (hwaddr)-1) {


        plen = TARGET_PAGE_SIZE;
    }


    plen -= 1;

    return (IOMMUTLBEntry) {
        .target_as = section.address_space,
        .iova = addr & ~plen,
        .translated_addr = xlat & ~plen,
        .addr_mask = plen,

        .perm = IOMMU_RW,
    };

iotlb_fail:
    return (IOMMUTLBEntry) {0};
}
