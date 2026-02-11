find_section_by_address (bfd_vma addr)
{
  unsigned int i;

  for (i = 0; i < elf_header.e_shnum; i++)
    {
      Elf_Internal_Shdr *sec = section_headers + i;
      if (addr >= sec->sh_addr && addr < sec->sh_addr + sec->sh_size)
	return sec;
    }

  return NULL;
}
