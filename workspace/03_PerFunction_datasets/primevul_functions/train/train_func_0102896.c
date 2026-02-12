void PackLinuxElf32::pack3(OutputFile *fo, Filter &ft)
{
    super::pack3(fo, ft);

    unsigned total_in = 0, total_out = 0;
    for (unsigned k = 0; k < e_phnum; ++k) {
        Extent x;
        x.size = find_LOAD_gap(phdri, k, e_phnum);
        if (x.size) {
            x.offset = get_te32(&phdri[k].p_offset) +
                       get_te32(&phdri[k].p_filesz);
            packExtent(x, total_in, total_out, 0, fo);
        }
    }

    b_info hdr; memset(&hdr, 0, sizeof(hdr));
    set_le32(&hdr.sz_cpr, UPX_MAGIC_LE32);
    fo->write(&hdr, sizeof(hdr));
    fpad4(fo);

    set_te32(&elfout.phdr[0].p_filesz, sz_pack2 + lsize);
    set_te32(&elfout.phdr[0].p_memsz,  sz_pack2 + lsize);
    if (0!=xct_off) {
        Elf32_Phdr *phdr = phdri;
        unsigned off = fo->st_size();
        unsigned off_init = 0;
        unsigned va_init = sz_pack2;
        so_slide = 0;
        for (int j = e_phnum; --j>=0; ++phdr) {
            unsigned const len  = get_te32(&phdr->p_filesz);
            unsigned const ioff = get_te32(&phdr->p_offset);
            unsigned const type = get_te32(&phdr->p_type);
            if (phdr->PT_INTERP==type) {


                memcpy((unsigned char *)ibuf, phdr, sizeof(*phdr));
                memmove(phdr, 1+phdr, j * sizeof(*phdr));
                memcpy(&phdr[j], (unsigned char *)ibuf, sizeof(*phdr));
                --phdr;
                set_te16(&ehdri.e_phnum, --e_phnum);
                continue;
            }
            if (phdr->PT_LOAD32==type) {
                if (xct_off < ioff) {
                    fi->seek(ioff, SEEK_SET);
                    fi->readx(ibuf, len);
                    off += ~page_mask & (ioff - off);
                    fo->seek(off, SEEK_SET);
                    fo->write(ibuf, len);
                    so_slide = off - ioff;
                    set_te32(&phdr->p_offset, so_slide + ioff);
                }
                else {
                    va_init += get_te32(&phdr->p_vaddr);
                    set_te32(&phdr->p_filesz, sz_pack2 + lsize);
                    set_te32(&phdr->p_memsz,  sz_pack2 + lsize);
                }
                continue;
            }

            if ( phdr->PT_DYNAMIC==type) {
                off_init = so_slide + ioff;
                fi->seek(ioff, SEEK_SET);
                fi->read(ibuf, len);
                Elf32_Dyn *dyn = (Elf32_Dyn *)(void *)ibuf;
                for (int j2 = len; j2 > 0; ++dyn, j2 -= sizeof(*dyn)) {
                    if (dyn->DT_INIT==get_te32(&dyn->d_tag)) {
                        unsigned const t = (unsigned char *)&dyn->d_val -
                                           (unsigned char *)ibuf;
                        off_init += t;
                        break;
                    }
                }

            }
            if (xct_off < ioff)
                set_te32(&phdr->p_offset, so_slide + ioff);
        }
        if (off_init) {
            fo->seek(off_init, SEEK_SET);
            va_init |= (Elf32_Ehdr::EM_ARM==e_machine);
            unsigned word; set_te32(&word, va_init);
            fo->rewrite(&word, sizeof(word));
            fo->seek(0, SEEK_END);
        }
        ehdri.e_shnum = 0;
        ehdri.e_shoff = 0;
        ehdri.e_shstrndx = 0;
    }
}
