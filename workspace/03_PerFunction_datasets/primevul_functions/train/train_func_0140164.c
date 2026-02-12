off_t PackLinuxElf64::pack3(OutputFile *fo, Filter &ft)
{
    off_t flen = super::pack3(fo, ft);


    unsigned v_hole = sz_pack2 + lsize;
    set_te64(&elfout.phdr[C_TEXT].p_filesz, v_hole);
    set_te64(&elfout.phdr[C_TEXT].p_memsz,  v_hole);

    for (unsigned k = 0; k < e_phnum; ++k) {
        Extent x;
        x.size = find_LOAD_gap(phdri, k, e_phnum);
        if (x.size) {
            x.offset = get_te64(&phdri[k].p_offset) +
                       get_te64(&phdri[k].p_filesz);
            packExtent(x, nullptr, fo);
        }
    }

    b_info hdr; memset(&hdr, 0, sizeof(hdr));
    set_le32(&hdr.sz_cpr, UPX_MAGIC_LE32);
    fo->write(&hdr, sizeof(hdr));
    flen = fpad4(fo);

    set_te64(&elfout.phdr[C_TEXT].p_filesz, sz_pack2 + lsize);
    set_te64(&elfout.phdr[C_TEXT].p_memsz,  sz_pack2 + lsize);
    if (0==xct_off) {
        set_te64(&elfout.phdr[C_BASE].p_align, ((upx_uint64_t)0) - page_mask);
        elfout.phdr[C_BASE].p_paddr = elfout.phdr[C_BASE].p_vaddr;
        elfout.phdr[C_BASE].p_offset = 0;
        upx_uint64_t abrk = getbrk(phdri, e_phnum);

        upx_uint64_t const vbase = get_te64(&elfout.phdr[C_BASE].p_vaddr);
        set_te64(&elfout.phdr[C_BASE].p_filesz, 0x1000);
        set_te64(&elfout.phdr[C_BASE].p_memsz, abrk - vbase);
        set_te32(&elfout.phdr[C_BASE].p_flags, Elf32_Phdr::PF_W|Elf32_Phdr::PF_R);
        set_te64(&elfout.phdr[C_TEXT].p_vaddr, abrk= (page_mask & (~page_mask + abrk)));
        elfout.phdr[C_TEXT].p_paddr = elfout.phdr[C_TEXT].p_vaddr;
        set_te64(&elfout.ehdr.e_entry, abrk + get_te64(&elfout.ehdr.e_entry) - vbase);
    }
    if (0!=xct_off) {
        upx_uint64_t word = load_va + sz_pack2;
        set_te64(&file_image[user_init_off], word);

        Elf64_Phdr *phdr = (Elf64_Phdr *)lowmem.subref(
                "bad e_phoff", e_phoff, e_phnum * sizeof(Elf64_Phdr));
        unsigned off = fo->st_size();
        so_slide = 0;
        for (unsigned j = 0; j < e_phnum; ++j, ++phdr) {
            upx_uint64_t const len  = get_te64(&phdr->p_filesz);
            upx_uint64_t const ioff = get_te64(&phdri[j].p_offset);
            upx_uint64_t       align= get_te64(&phdr->p_align);
            unsigned const type = get_te32(&phdr->p_type);
            if (Elf64_Phdr::PT_INTERP==type) {


                memcpy((unsigned char *)ibuf, phdr, sizeof(*phdr));
                memmove(phdr, 1+phdr, (e_phnum - (1+ j))*sizeof(*phdr));
                memcpy(&phdr[e_phnum - (1+ j)], (unsigned char *)ibuf, sizeof(*phdr));
                --phdr; --e_phnum;
                set_te16(&ehdri.e_phnum, e_phnum);
                set_te16(&((Elf64_Ehdr *)(unsigned char *)lowmem)->e_phnum, e_phnum);
                continue;
            }
            if (PT_LOAD64 == type) {
                if ((xct_off - ioff) < len) {
                    set_te64(&phdr->p_filesz, sz_pack2 + lsize - ioff);
                    set_te64(&phdr->p_memsz,  sz_pack2 + lsize - ioff);
                    if (user_init_off < xct_off) {

                        unsigned off2 = user_init_off - sizeof(word);
                        fo->seek(off2, SEEK_SET);
                        fo->rewrite(&file_image[off2], 2*sizeof(word));
                    }
                }
                else if (xct_off < ioff) {


                    if ((1u<<12) < align
                    &&  Elf64_Ehdr::EM_X86_64 ==e_machine
                    ) {
                        align = 1u<<12;
                        set_te64(&phdr->p_align, align);
                    }
                    off += (align-1) & (ioff - off);
                    set_te64(&phdr->p_offset, off);
                    so_slide = off - ioff;
                    fo->seek(  off, SEEK_SET);
                    fo->write(&file_image[ioff], len);
                    off += len;
                }
                continue;
            }
            if (xct_off < ioff)
                set_te64(&phdr->p_offset, so_slide + ioff);
        }

        if (opt->o_unix.android_shlib) {

            Elf64_Shdr *shdr = (Elf64_Shdr *)lowmem.subref(
                    "bad e_shoff", xct_off - asl_delta, e_shnum * sizeof(Elf64_Shdr));
            for (unsigned j = 0; j < e_shnum; ++shdr, ++j) {
                unsigned sh_type = get_te32(&shdr->sh_type);
                if (Elf64_Shdr::SHT_DYNAMIC == sh_type) {
                    upx_uint64_t offset = get_te64(&shdr->sh_offset);
                    set_te64(&shdr->sh_offset, so_slide + offset);
                    fo->seek((j * sizeof(Elf64_Shdr)) + xct_off - asl_delta, SEEK_SET);
                    fo->rewrite(shdr, sizeof(*shdr));
                    fo->seek(0, SEEK_END);
                }
                if (Elf64_Shdr::SHT_RELA == sh_type
                &&  n_jmp_slot
                &&  !strcmp(".rela.plt", get_te32(&shdr->sh_name) + shstrtab)) {
                    upx_uint64_t f_off = elf_get_offset_from_address(plt_off);
                    fo->seek(so_slide + f_off, SEEK_SET);
                    fo->rewrite(&file_image[f_off], n_jmp_slot * 8);
                }
            }
        }
        else {
            ehdri.e_shnum = 0;
            ehdri.e_shoff = 0;
            ehdri.e_shstrndx = 0;
        }
    }
    return flen;
}
