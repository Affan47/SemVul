uc_err uc_mem_unmap(struct uc_struct *uc, uint64_t address, size_t size)
{
    MemoryRegion *mr;
    uint64_t addr;
    size_t count, len;

    UC_INIT(uc);

    if (size == 0) {

        return UC_ERR_OK;
    }


    if ((address & uc->target_page_align) != 0) {
        return UC_ERR_ARG;
    }


    if ((size & uc->target_page_align) != 0) {
        return UC_ERR_ARG;
    }

    if (uc->mem_redirect) {
        address = uc->mem_redirect(address);
    }


    if (!check_mem_area(uc, address, size)) {
        return UC_ERR_NOMEM;
    }


    addr = address;
    count = 0;
    while (count < size) {
        mr = memory_mapping(uc, addr);
        len = (size_t)MIN(size - count, mr->end - addr);
        if (!split_region(uc, mr, addr, len, true)) {
            return UC_ERR_NOMEM;
        }


        mr = memory_mapping(uc, addr);
        if (mr != NULL) {
            uc->memory_unmap(uc, mr);
        }
        count += len;
        addr += len;
    }

    return UC_ERR_OK;
}
