void PackLinuxElf32mipseb::defineSymbols(Filter const *ft)
{
    PackLinuxElf32::defineSymbols(ft);

    unsigned const hlen = sz_elf_hdrs + sizeof(l_info) + sizeof(p_info);


    unsigned len = 0;
    unsigned lo_va_user = ~0u;
    for (int j= e_phnum; --j>=0; ) {
        if (PT_LOAD32 == get_te32(&phdri[j].p_type)) {
            len += (unsigned)get_te32(&phdri[j].p_filesz);
            unsigned const va = get_te32(&phdri[j].p_vaddr);
            if (va < lo_va_user) {
                lo_va_user = va;
            }
        }
    }
    lsize =   64 * 1024;
    unsigned lo_va_stub = get_te32(&elfout.phdr[0].p_vaddr);
    unsigned adrc;
    unsigned adrm;
    unsigned adru;
    unsigned adrx;
    unsigned lenm;
    unsigned lenu;
    len += (7&-lsize) + lsize;
    is_big = (lo_va_user < (lo_va_stub + len + 2*page_size));
    if (is_big) {
        set_te32(    &elfout.ehdr.e_entry,
            get_te32(&elfout.ehdr.e_entry) + lo_va_user - lo_va_stub);
        set_te32(&elfout.phdr[0].p_vaddr, lo_va_user);
        set_te32(&elfout.phdr[0].p_paddr, lo_va_user);
               lo_va_stub      = lo_va_user;
        adrc = lo_va_stub;
        adrm = getbrk(phdri, e_phnum);
        adru = page_mask & (~page_mask + adrm);
        adrx = adru + hlen;
        lenm = page_size + len;
        lenu = page_size + len;
    }
    else {
        adrm = lo_va_stub + len;
        adrc = adrm;
        adru = lo_va_stub;
        adrx = lo_va_stub + hlen;
        lenm = page_size;
        lenu = page_size + len;
    }
    adrm = page_mask & (~page_mask + adrm);
    adrc = page_mask & (~page_mask + adrc);

    linker->defineSymbol("ADRX", adrx);

    linker->defineSymbol("ADRC", adrc);
    linker->defineSymbol("LENU", lenu);
    linker->defineSymbol("ADRU", adru);
    linker->defineSymbol("LENM", lenm);
    linker->defineSymbol("ADRM", adrm);


}
