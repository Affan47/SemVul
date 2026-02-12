PackLinuxElf64amd::defineSymbols(Filter const *ft)
{
    PackLinuxElf64::defineSymbols(ft);


    unsigned len = 0;
    upx_uint64_t lo_va_user = ~0ull;
    for (int j= e_phnum; --j>=0; ) {
        if (PT_LOAD64 == get_te32(&phdri[j].p_type)) {
            len += (unsigned)get_te64(&phdri[j].p_filesz);
            upx_uint64_t const va = get_te64(&phdri[j].p_vaddr);
            if (va < lo_va_user) {
                lo_va_user = va;
            }
        }
    }
    lsize =   64 * 1024;
    upx_uint64_t       lo_va_stub = get_te64(&elfout.phdr[0].p_vaddr);
    upx_uint64_t adrm;
    unsigned lenm;
    unsigned lenu;
    len += (7&-lsize) + lsize;
    const upx_uint64_t my_page_size = 4096u;
    const upx_uint64_t my_page_mask = 0u - my_page_size;
    is_big = (lo_va_user < (lo_va_stub + len + 2 * my_page_size));
    if (is_pie || (is_big )) {

        set_te64(    &elfout.ehdr.e_entry,
            get_te64(&elfout.ehdr.e_entry) + lo_va_user - lo_va_stub);
        set_te64(&elfout.phdr[0].p_vaddr, lo_va_user);
        set_te64(&elfout.phdr[0].p_paddr, lo_va_user);
               lo_va_stub      = lo_va_user;
        adrm = getbrk(phdri, e_phnum) - lo_va_user;
        lenm = my_page_size + len;
        lenu = my_page_size + len;
    }
    else {
        adrm = len;
        lenm = my_page_size;
        lenu = my_page_size + len;
    }
    adrm = my_page_mask & (~my_page_mask + adrm);

    linker->defineSymbol("LENU", lenu);
    linker->defineSymbol("LENM", lenm);
    linker->defineSymbol("ADRM", adrm);


}
