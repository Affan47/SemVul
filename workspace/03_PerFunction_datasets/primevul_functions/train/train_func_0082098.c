__fdnlist(int fd, struct nlist *list)
{
	struct nlist *p;
	Elf_Off symoff = 0, symstroff = 0;
	Elf_Word symsize = 0, symstrsize = 0;
	Elf_Sword cc, i;
	int nent = -1;
	int errsave;
	Elf_Sym sbuf[1024];
	Elf_Sym *s;
	Elf_Ehdr ehdr;
	char *strtab = NULL;
	Elf_Shdr *shdr = NULL;
	Elf_Word shdr_size;
	struct stat st;


	if (lseek(fd, (off_t)0, SEEK_SET) == -1 ||
	    read(fd, &ehdr, sizeof(Elf_Ehdr)) != sizeof(Elf_Ehdr) ||
	    !__elf_is_okay__(&ehdr) ||
	    fstat(fd, &st) < 0)
		return (-1);

	if (ehdr.e_shnum == 0 ||
	    ehdr.e_shentsize != sizeof(Elf_Shdr)) {
		errno = ERANGE;
		return (-1);
	}


	shdr_size = ehdr.e_shentsize * ehdr.e_shnum;


	if (shdr_size > SIZE_T_MAX || shdr_size > st.st_size) {
		errno = EFBIG;
		return (-1);
	}

	shdr = malloc((size_t)shdr_size);
	if (shdr == NULL)
		return (-1);


	if (pread(fd, shdr, (size_t)shdr_size, (off_t)ehdr.e_shoff) != (ssize_t)shdr_size)
		goto done;


	for (i = 0; i < ehdr.e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			if (shdr[i].sh_link >= ehdr.e_shnum)
				goto done;

			symoff = shdr[i].sh_offset;
			symsize = shdr[i].sh_size;
			symstroff = shdr[shdr[i].sh_link].sh_offset;
			symstrsize = shdr[shdr[i].sh_link].sh_size;
			break;
		}
	}


	if (symstrsize > SIZE_T_MAX || symstrsize > st.st_size) {
		errno = EFBIG;
		goto done;
	}


	strtab = malloc((size_t)symstrsize);
	if (strtab == NULL)
		goto done;

	if (pread(fd, strtab, (size_t)symstrsize, (off_t)symstroff) != (ssize_t)symstrsize)
		goto done;


	nent = 0;
	for (p = list; !ISLAST(p); ++p) {
		p->n_type = 0;
		p->n_other = 0;
		p->n_desc = 0;
		p->n_value = 0;
		++nent;
	}


	if (symoff == 0)
		goto done;

	if (lseek(fd, (off_t) symoff, SEEK_SET) == -1) {
		nent = -1;
		goto done;
	}

	while (symsize > 0 && nent > 0) {
		cc = MIN(symsize, sizeof(sbuf));
		if (read(fd, sbuf, cc) != cc)
			break;
		symsize -= cc;
		for (s = sbuf; cc > 0 && nent > 0; ++s, cc -= sizeof(*s)) {
			char *name;
			struct nlist *p;

			name = strtab + s->st_name;
			if (name[0] == '\0')
				continue;

			for (p = list; !ISLAST(p); p++) {
				if ((p->n_un.n_name[0] == '_' &&
				    strcmp(name, p->n_un.n_name+1) == 0)
				    || strcmp(name, p->n_un.n_name) == 0) {
					elf_sym_to_nlist(p, s, shdr,
					    ehdr.e_shnum);
					if (--nent <= 0)
						break;
				}
			}
		}
	}
  done:
	errsave = errno;
	free(strtab);
	free(shdr);
	errno = errsave;
	return (nent);
}
