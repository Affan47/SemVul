elf_x86_probe(const char *buf, off_t len)
{

	struct mem_ehdr ehdr;
	int result;
	result = build_elf_exec_info(buf, len, &ehdr, 0);
	if (result < 0) {
		if (probe_debug) {
			fprintf(stderr, "Not an ELF executable\n");
		}
		goto out;
	}


	if ((ehdr.e_machine != EM_386) && (ehdr.e_machine != EM_486)) {

		if (probe_debug) {
			fprintf(stderr, "Not i386 ELF executable\n");
		}
		result = -1;
		goto out;
	}
	result = 0;
 out:
	free_elf_info(&ehdr);
	return result;
}
