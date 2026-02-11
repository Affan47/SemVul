elf_machine_rel (struct link_map *map, const Elf32_Rel *reloc,
		 const Elf32_Sym *sym, Elf32_Addr *const reloc_addr)
{
	Elf32_Addr ls_addr, s_addr;
	Elf32_Addr value;
	if (ELF32_R_TYPE (reloc->r_info) == R_386_RELATIVE)
	{
		*reloc_addr += map->l_addr - map->ll_addr;
		return;
	}
	if (ELF32_R_TYPE(reloc->r_info) == R_386_NONE) {
		return;
	}
	value = sym->st_value;

	ls_addr = sym->st_shndx == SHN_UNDEF ? 0 : map->ll_addr;
	s_addr = sym->st_shndx == SHN_UNDEF ? 0 : map->l_addr;

	switch (ELF32_R_TYPE (reloc->r_info))
	{
	case R_386_COPY:
	{

		unsigned char *dest, *src;
		long i;
		dest = (unsigned char *)reloc_addr;
		src = (unsigned char *)(value + s_addr);
		for(i = 0; i < sym->st_size; i++) {
			dest[i] = src[i];
		}
	}
	break;
	case R_386_GLOB_DAT:
		*reloc_addr = s_addr + value;
		break;
	case R_386_JMP_SLOT:
		*reloc_addr = s_addr + value;
		break;
	case R_386_32:
		if (map->ll_addr == 0) {
			*reloc_addr += value;
		}
		*reloc_addr += s_addr - ls_addr;
		break;
	case R_386_PC32:
		if (map->ll_addr == 0) {
			*reloc_addr += value - reloc->r_offset;
		}
		*reloc_addr += (s_addr - map->l_addr) - (ls_addr - map->ll_addr);
		break;
	default:
		assert (! "unexpected dynamic reloc type");
		break;
	}
}
