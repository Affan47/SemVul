_bfd_elf_set_osabi (bfd * abfd,
		    struct bfd_link_info * link_info ATTRIBUTE_UNUSED)
{
  Elf_Internal_Ehdr * i_ehdrp;

  i_ehdrp = elf_elfheader (abfd);

  i_ehdrp->e_ident[EI_OSABI] = get_elf_backend_data (abfd)->elf_osabi;


  if (i_ehdrp->e_ident[EI_OSABI] == ELFOSABI_NONE
      && elf_tdata (abfd)->has_gnu_symbols)
    i_ehdrp->e_ident[EI_OSABI] = ELFOSABI_GNU;
}
