void PackLinuxElf32::defineSymbols(Filter const *ft)
{
    PackLinuxElf::defineSymbols(ft);


    unsigned len = 0;
    upx_uint32_t lo_va_user = ~0u;
    for (int j= e_phnum; --j>=0; ) {
        if (PT_LOAD32 == get_te32(&phdri[j].p_type)) {
            len += (unsigned)get_te32(&phdri[j].p_filesz);
            upx_uint32_t const va = get_te32(&phdri[j].p_vaddr);
            if (va < lo_va_user) {
                lo_va_user = va;
            }
        }
    }
    lsize =   64 * 1024;
    upx_uint32_t       lo_va_stub = get_te32(&elfout.phdr[0].p_vaddr);
    upx_uint32_t adrm;
    len += (7&-lsize) + lsize;
    const upx_uint32_t my_page_size = 4096u;
    const upx_uint32_t my_page_mask = 0u - my_page_size;
    is_big = (lo_va_user < (lo_va_stub + len + 2 * my_page_size));
    if (is_pie || (is_big )) {

        set_te32(    &elfout.ehdr.e_entry,
            get_te32(&elfout.ehdr.e_entry) + lo_va_user - lo_va_stub);
        set_te32(&elfout.phdr[0].p_vaddr, lo_va_user);
        set_te32(&elfout.phdr[0].p_paddr, lo_va_user);
               lo_va_stub      = lo_va_user;
        adrm = getbrk(phdri, e_phnum) - lo_va_user;
    }
    else {
        adrm = len;
    }
    adrm = my_page_mask & (~my_page_mask + adrm);


}
