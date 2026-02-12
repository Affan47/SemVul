uc_err uc_mem_protect(struct uc_struct *uc, uint64_t address, size_t size,
                      uint32_t perms)
{
    MemoryRegion *mr;
    uint64_t addr = address;
    size_t count, len;
    bool remove_exec = false;

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


    if ((perms & ~UC_PROT_ALL) != 0) {
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
        if (!split_region(uc, mr, addr, len, false)) {
            return UC_ERR_NOMEM;
        }

        mr = memory_mapping(uc, addr);

        if (((mr->perms & UC_PROT_EXEC) != 0) &&
            ((perms & UC_PROT_EXEC) == 0)) {
            remove_exec = true;
        }
        mr->perms = perms;
        uc->readonly_mem(mr, (perms & UC_PROT_WRITE) == 0);

        count += len;
        addr += len;
    }


    if (remove_exec) {
        uc->quit_request = true;
        uc_emu_stop(uc);
    }

    return UC_ERR_OK;
}
