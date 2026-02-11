elf_sym(struct mem_ehdr *ehdr, const unsigned char *ptr)
{
	struct mem_sym sym = { 0, 0, 0, 0, 0, 0 };
	if (ehdr->ei_class == ELFCLASS32) {
		Elf32_Sym lsym;
		memcpy(&lsym, ptr, sizeof(lsym));
		sym.st_name  = elf32_to_cpu(ehdr, lsym.st_name);
		sym.st_value = elf32_to_cpu(ehdr, lsym.st_value);
		sym.st_size  = elf32_to_cpu(ehdr, lsym.st_size);
		sym.st_info  = lsym.st_info;
		sym.st_other = lsym.st_other;
		sym.st_shndx = elf16_to_cpu(ehdr, lsym.st_shndx);
	}
	else if (ehdr->ei_class == ELFCLASS64) {
		Elf64_Sym lsym;
		memcpy(&lsym, ptr, sizeof(lsym));
		sym.st_name  = elf32_to_cpu(ehdr, lsym.st_name);
		sym.st_value = elf64_to_cpu(ehdr, lsym.st_value);
		sym.st_size  = elf64_to_cpu(ehdr, lsym.st_size);
		sym.st_info  = lsym.st_info;
		sym.st_other = lsym.st_other;
		sym.st_shndx = elf16_to_cpu(ehdr, lsym.st_shndx);
	}
	else {
		die("Bad elf class");
	}
	return sym;
}
