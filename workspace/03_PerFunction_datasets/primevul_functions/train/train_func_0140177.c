void PackLinuxElf32::unpack(OutputFile *fo)
{
    if (e_phoff != sizeof(Elf32_Ehdr)) {
        throwCantUnpack("bad e_phoff");
    }
    unsigned const c_phnum = get_te16(&ehdri.e_phnum);
    unsigned old_dtinit = 0;
    unsigned is_asl = 0;

    unsigned szb_info = sizeof(b_info);
    {
        if (get_te32(&ehdri.e_entry) < 0x401180
        &&  Elf32_Ehdr::EM_386 ==get_te16(&ehdri.e_machine)
        &&  Elf32_Ehdr::ET_EXEC==get_te16(&ehdri.e_type)) {


            szb_info = 2*sizeof(unsigned);
        }
    }

    fi->seek(overlay_offset - sizeof(l_info), SEEK_SET);
    fi->readx(&linfo, sizeof(linfo));
    lsize = get_te16(&linfo.l_lsize);
    if (UPX_MAGIC_LE32 != get_le32(&linfo.l_magic)) {
        throwCantUnpack("l_info corrupted");
    }
    p_info hbuf;  fi->readx(&hbuf, sizeof(hbuf));
    unsigned orig_file_size = get_te32(&hbuf.p_filesize);
    blocksize = get_te32(&hbuf.p_blocksize);
    if ((u32_t)file_size > orig_file_size || blocksize > orig_file_size
        || !mem_size_valid(1, blocksize, OVERHEAD))
        throwCantUnpack("p_info corrupted");

    ibuf.alloc(blocksize + OVERHEAD);
    b_info bhdr; memset(&bhdr, 0, sizeof(bhdr));
    fi->readx(&bhdr, szb_info);
    ph.u_len = get_te32(&bhdr.sz_unc);
    ph.c_len = get_te32(&bhdr.sz_cpr);
    if (ph.c_len > (unsigned)file_size || ph.c_len == 0 || ph.u_len == 0
    ||  ph.u_len > orig_file_size)
        throwCantUnpack("b_info corrupted");
    ph.filter_cto = bhdr.b_cto8;

    MemBuffer u(ph.u_len);
    Elf32_Ehdr *const ehdr = (Elf32_Ehdr *)&u[0];
    Elf32_Phdr const *phdr = nullptr;


    if (ibuf.getSize() < ph.c_len) {
        throwCompressedDataViolation();
    }
    fi->readx(ibuf, ph.c_len);
    decompress(ibuf, (upx_byte *)ehdr, false);
    if (ehdr->e_type   !=ehdri.e_type
    ||  ehdr->e_machine!=ehdri.e_machine
    ||  ehdr->e_version!=ehdri.e_version
    ||  ehdr->e_flags  !=ehdri.e_flags
    ||  ehdr->e_ehsize !=ehdri.e_ehsize

    ||  memcmp(ehdr->e_ident, ehdri.e_ident, Elf32_Ehdr::EI_OSABI)) {
        throwCantUnpack("ElfXX_Ehdr corrupted");
    }
    fi->seek(- (off_t) (szb_info + ph.c_len), SEEK_CUR);

    unsigned const u_phnum = get_te16(&ehdr->e_phnum);
    total_in = 0;
    total_out = 0;
    unsigned c_adler = upx_adler32(nullptr, 0);
    unsigned u_adler = upx_adler32(nullptr, 0);
#define MAX_ELF_HDR 512
    if ((umin(MAX_ELF_HDR, ph.u_len) - sizeof(Elf32_Ehdr))/sizeof(Elf32_Phdr) < u_phnum) {
        throwCantUnpack("bad compressed e_phnum");
    }
#undef MAX_ELF_HDR


    Elf32_Phdr const *const dynhdr = elf_find_ptype(Elf32_Phdr::PT_DYNAMIC, phdri, c_phnum);
    bool const is_shlib = !!dynhdr;
    if (is_shlib) {


        unpackExtent(ph.u_len, fo,
            c_adler, u_adler, false, szb_info);


        fi->seek(0, SEEK_SET);
        fi->readx(ibuf, get_te32(&dynhdr->p_offset) + get_te32(&dynhdr->p_filesz));
        overlay_offset -= sizeof(linfo);
        xct_off = overlay_offset;
        e_shoff = get_te32(&ehdri.e_shoff);
        ibuf.subref("bad .e_shoff %#x for %#x", e_shoff, sizeof(Elf32_Shdr) * e_shnum);
        if (e_shoff && e_shnum) {
            shdri = (Elf32_Shdr  *)ibuf.subref(
                "bad Shdr table", e_shoff, sizeof(Elf32_Shdr)*e_shnum);
            unsigned xct_off2 = get_te32(&shdri->sh_offset);
            if (e_shoff == xct_off2) {
                xct_off = e_shoff;
            }

            unsigned dyn_offset = get_te32(&dynhdr->p_offset);
            unsigned dyn_filesz = get_te32(&dynhdr->p_filesz);
            if (orig_file_size < dyn_offset
            || (orig_file_size - dyn_offset) < dyn_filesz) {
                throwCantUnpack("bad PT_DYNAMIC");
            }
            dynseg = (Elf32_Dyn const *)ibuf.subref("bad DYNAMIC", dyn_offset, dyn_filesz);
            dynstr = (char const *)elf_find_dynamic(Elf32_Dyn::DT_STRTAB);
            sec_dynsym = elf_find_section_type(Elf32_Shdr::SHT_DYNSYM);
            if (sec_dynsym) {
                unsigned const off_dynsym = get_te32(&sec_dynsym->sh_offset);
                unsigned const sz_dynsym  = get_te32(&sec_dynsym->sh_size);
                if (orig_file_size < sz_dynsym
                ||  orig_file_size < off_dynsym
                || (orig_file_size - off_dynsym) < sz_dynsym) {
                    throwCantUnpack("bad SHT_DYNSYM");
                }
                Elf32_Sym *const sym0 = (Elf32_Sym *)ibuf.subref(
                    "bad dynsym", off_dynsym, sz_dynsym);
                Elf32_Sym *sym = sym0;
                for (int j = sz_dynsym / sizeof(Elf32_Sym); --j>=0; ++sym) {
                    unsigned symval = get_te32(&sym->st_value);
                    unsigned symsec = get_te16(&sym->st_shndx);
                    if (Elf32_Sym::SHN_UNDEF != symsec
                    &&  Elf32_Sym::SHN_ABS   != symsec
                    &&  xct_off <= symval) {
                        set_te32(&sym->st_value, symval - asl_delta);
                    }
                    if (Elf32_Sym::SHN_ABS == symsec && xct_off <= symval) {
                        adjABS(sym, 0u - asl_delta);
                    }
                }
            }
        }
        if (fo) {
            fo->write(ibuf + ph.u_len, xct_off - ph.u_len);
        }

        total_in  = xct_off;
        total_out = xct_off;
        ph.u_len = 0;

        fi->seek(sizeof(linfo) + overlay_offset + sizeof(hbuf) + szb_info + ph.c_len, SEEK_SET);


        phdr = (Elf32_Phdr *) (void *) (1+ ehdr);
        for (unsigned j=0; j < u_phnum; ++phdr, ++j) {
            if (is_LOAD32(phdr)) {
                ph.u_len = get_te32(&phdr->p_filesz) - xct_off;
                break;
            }
        }
        unpackExtent(ph.u_len, fo,
            c_adler, u_adler, false, szb_info);
    }
    else {

        bool first_PF_X = true;
        phdr = (Elf32_Phdr *) (void *) (1+ ehdr);
        for (unsigned j=0; j < u_phnum; ++phdr, ++j) {
            if (is_LOAD32(phdr)) {
                unsigned const filesz = get_te32(&phdr->p_filesz);
                unsigned const offset = get_te32(&phdr->p_offset);
                if (fo)
                    fo->seek(offset, SEEK_SET);
                if (Elf32_Phdr::PF_X & get_te32(&phdr->p_flags)) {
                    unpackExtent(filesz, fo,
                        c_adler, u_adler, first_PF_X, szb_info);
                    first_PF_X = false;
                }
                else {
                    unpackExtent(filesz, fo,
                        c_adler, u_adler, false, szb_info);
                }
            }
        }
    }
    phdr = phdri;
    load_va = 0;
    for (unsigned j=0; j < c_phnum; ++j) {
        if (is_LOAD32(phdr)) {
            load_va = get_te32(&phdr->p_vaddr);
            break;
        }
    }
    if (0x1000==get_te32(&phdri[0].p_filesz)
    &&  0==get_te32(&phdri[1].p_offset)
    &&  0==get_te32(&phdri[0].p_offset)
    &&     get_te32(&phdri[1].p_filesz) == get_te32(&phdri[1].p_memsz)) {
        fi->seek(up4(get_te32(&phdr[1].p_memsz)), SEEK_SET);
    }
    else if (is_shlib
    ||  ((unsigned)(get_te32(&ehdri.e_entry) - load_va) + up4(lsize) +
                ph.getPackHeaderSize() + sizeof(overlay_offset))
            < up4(file_size)) {

        funpad4(fi);
        unsigned d_info[4]; fi->readx(d_info, sizeof(d_info));
        if (0==old_dtinit) {
            old_dtinit = get_te32(&d_info[2 + (0==d_info[0])]);
            is_asl = 1u& get_te32(&d_info[0 + (0==d_info[0])]);
        }
        fi->seek(lsize - sizeof(d_info), SEEK_CUR);
    }


    phdr = (Elf32_Phdr *)&u[sizeof(*ehdr)];
    unsigned hi_offset(0);
    for (unsigned j = 0; j < u_phnum; ++j) {
        unsigned offset = get_te32(&phdr[j].p_offset);
        if (is_LOAD32(&phdr[j])
        &&  hi_offset < offset)
            hi_offset = offset;
    }
    for (unsigned j = 0; j < u_phnum; ++j) {
        unsigned const size = find_LOAD_gap(phdr, j, u_phnum);
        if (size) {
            unsigned const offset = get_te32(&phdr[j].p_offset);
            unsigned const where =  get_te32(&phdr[j].p_filesz) + offset;
            if (fo)
                fo->seek(where, SEEK_SET);
            unpackExtent(size, fo,
                c_adler, u_adler, false, szb_info,
                is_shlib && (offset != hi_offset));

        }
    }


    fi->readx(&bhdr, szb_info);
    unsigned const sz_unc = ph.u_len = get_te32(&bhdr.sz_unc);

    if (sz_unc == 0) {

        unsigned const sz_cpr = get_le32(&bhdr.sz_cpr);
        if (sz_cpr != UPX_MAGIC_LE32)
            throwCompressedDataViolation();
    }
    else {
        throwCompressedDataViolation();
    }

    if (is_shlib) {


        int n_ptload = 0;
        unsigned load_off = 0;
        phdr = (Elf32_Phdr *)&u[sizeof(*ehdr)];
        for (unsigned j= 0; j < u_phnum; ++j, ++phdr) {
            if (is_LOAD32(phdr) && 0!=n_ptload++) {
                load_off = get_te32(&phdr->p_offset);
                load_va  = get_te32(&phdr->p_vaddr);
                fi->seek(old_data_off, SEEK_SET);
                fi->readx(ibuf, old_data_len);
                total_in  += old_data_len;
                total_out += old_data_len;

                Elf32_Phdr const *udynhdr = (Elf32_Phdr *)&u[sizeof(*ehdr)];
                for (unsigned j3= 0; j3 < u_phnum; ++j3, ++udynhdr)
                if (Elf32_Phdr::PT_DYNAMIC==get_te32(&udynhdr->p_type)) {
                    unsigned dt_pltrelsz(0), dt_jmprel(0);
                    unsigned dt_relsz(0), dt_rel(0);
                    unsigned const dyn_len = get_te32(&udynhdr->p_filesz);
                    unsigned const dyn_off = get_te32(&udynhdr->p_offset);
                    if ((unsigned long)file_size < (dyn_len + dyn_off)) {
                        char msg[50]; snprintf(msg, sizeof(msg),
                                "bad PT_DYNAMIC .p_filesz %#x", dyn_len);
                        throwCantUnpack(msg);
                    }
                    if (dyn_off < load_off) {
                        continue;
                    }
                    Elf32_Dyn *dyn = (Elf32_Dyn *)((unsigned char *)ibuf +
                        (dyn_off - load_off));
                    dynseg = dyn; invert_pt_dynamic(dynseg,
                        umin(dyn_len, file_size - dyn_off));
                    for (unsigned j2= 0; j2 < dyn_len; ++dyn, j2 += sizeof(*dyn)) {
                        unsigned const tag = get_te32(&dyn->d_tag);
                        unsigned       val = get_te32(&dyn->d_val);
                        if (is_asl) switch (tag) {
                        case Elf32_Dyn::DT_RELSZ:    { dt_relsz    = val; } break;
                        case Elf32_Dyn::DT_REL:      { dt_rel      = val; } break;
                        case Elf32_Dyn::DT_PLTRELSZ: { dt_pltrelsz = val; } break;
                        case Elf32_Dyn::DT_JMPREL:   { dt_jmprel   = val; } break;

                        case Elf32_Dyn::DT_PLTGOT:
                        case Elf32_Dyn::DT_PREINIT_ARRAY:
                        case Elf32_Dyn::DT_INIT_ARRAY:
                        case Elf32_Dyn::DT_FINI_ARRAY:
                        case Elf32_Dyn::DT_FINI: {
                            set_te32(&dyn->d_val, val -= asl_delta);
                        }; break;
                        }
                        if (upx_dt_init == tag) {
                            if (Elf32_Dyn::DT_INIT == tag) {
                                set_te32(&dyn->d_val, old_dtinit);
                                if (!old_dtinit) {
                                    dyn->d_tag = Elf32_Dyn::DT_NULL;
                                    dyn->d_val = 0;
                                }
                            }
                            else if (Elf32_Dyn::DT_INIT_ARRAY    == tag
                            ||       Elf32_Dyn::DT_PREINIT_ARRAY == tag) {
                                if (val < load_va || (unsigned)file_size < (unsigned)val) {
                                    char msg[50]; snprintf(msg, sizeof(msg),
                                            "Bad Dynamic tag %#x %#x",
                                            (unsigned)tag, (unsigned)val);
                                    throwCantUnpack(msg);
                                }
                                set_te32(&ibuf[val - load_va], old_dtinit
                                    + (is_asl ? asl_delta : 0));
                            }
                        }

                    }
                    if (is_asl) {
                        lowmem.alloc(xct_off);
                        fi->seek(0, SEEK_SET);
                        fi->read(lowmem, xct_off);
                        if (dt_relsz && dt_rel) {
                            Elf32_Rel *const rel0 = (Elf32_Rel *)lowmem.subref(
                                "bad Rel offset", dt_rel, dt_relsz);
                            unRel32(dt_rel, rel0, dt_relsz, ibuf, load_va, fo);
                        }
                        if (dt_pltrelsz && dt_jmprel) {
                            Elf32_Rel *const jmp0 = (Elf32_Rel *)lowmem.subref(
                                "bad Jmprel offset", dt_jmprel, dt_pltrelsz);
                            unRel32(dt_jmprel, jmp0, dt_pltrelsz, ibuf, load_va, fo);
                        }

                    }
                }
                if (fo) {
                    fo->seek(get_te32(&phdr->p_offset), SEEK_SET);
                    fo->rewrite(ibuf, old_data_len);
                }
            }
        }
    }


    ph.c_len = total_in;
    ph.u_len = total_out;


    if (fo && total_out != orig_file_size)
        throwEOFException();


    if (ph.c_adler != c_adler || ph.u_adler != u_adler)
        throwChecksumError();
}
