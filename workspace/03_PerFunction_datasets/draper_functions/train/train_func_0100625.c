elf_rand(Elf *elf, size_t offset) {
    if (!elf) {
	return 0;
    }
    elf_assert(elf->e_magic == ELF_MAGIC);
    if (elf->e_kind != ELF_K_AR) {
	seterr(ERROR_NOTARCHIVE);
    }
    else if (offset <= 0 || offset > elf->e_size) {
	seterr(ERROR_BADOFF);
    }
    else {
	elf->e_off = offset;
	return offset;
    }
    return 0;
}
