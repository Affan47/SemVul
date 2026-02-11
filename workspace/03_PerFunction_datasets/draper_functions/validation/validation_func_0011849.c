elf_find_nearest_line (ElfDesc *elfd, const ElfSection *section, ElfSymbol **syms,
		       vma_t vma, const char **filename, const char **symname,
		       unsigned int *lineno)
{
	unsigned char *ident;

	ident = elfd->hdr.hdr32.e_ident;

	if (ident[EI_CLASS] == ELFCLASS32)
		return elf32_find_nearest_line (elfd, section, syms, vma, filename, symname, lineno);
	else
		return elf64_find_nearest_line (elfd, section, syms, vma, filename, symname, lineno);
}
