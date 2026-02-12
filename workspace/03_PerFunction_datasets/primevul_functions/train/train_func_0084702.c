static uc_err mem_map_check(uc_engine *uc, uint64_t address, size_t size,
                            uint32_t perms)
{
    if (size == 0) {

        return UC_ERR_ARG;
    }


    if (address + size - 1 < address) {
        return UC_ERR_ARG;
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


    if (memory_overlap(uc, address, size)) {
        return UC_ERR_MAP;
    }

    return UC_ERR_OK;
}
