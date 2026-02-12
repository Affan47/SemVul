const RList *MACH0_(get_symbols_list)(struct MACH0_(obj_t) *bin) {
	static RList * cache = NULL;
	struct symbol_t *symbols;
	size_t j, s, symbols_size, symbols_count;
	ut32 to, from;
	size_t i;

	r_return_val_if_fail (bin, NULL);
	if (cache) {
		return cache;
	}
	RList *list = r_list_newf ((RListFree)r_bin_symbol_free);
	cache = list;

	HtPP *hash = ht_pp_new0 ();
	if (!hash) {
		return NULL;
	}

	walk_exports (bin, fill_exports_list, list);
	if (r_list_length (list)) {
		RListIter *it;
		RBinSymbol *s;
		r_list_foreach (list, it, s) {
			inSymtab (hash, s->name, s->vaddr);
		}
	}

	if (!bin->symtab || !bin->symstr) {
		ht_pp_free (hash);
		return list;
	}

	symbols_count = (bin->dysymtab.nextdefsym + \
			bin->dysymtab.nlocalsym + \
			bin->dysymtab.nundefsym );
	symbols_count += bin->nsymtab;
	symbols_size = (symbols_count + 1) * 2 * sizeof (struct symbol_t);

	if (symbols_size < 1 || !(symbols = calloc (1, symbols_size))) {
		ht_pp_free (hash);
		return NULL;
	}
	j = 0;
	bin->main_addr = 0;
	int bits = MACH0_(get_bits_from_hdr) (&bin->hdr);
	for (s = 0; s < 2; s++) {
		switch (s) {
		case 0:
			from = bin->dysymtab.iextdefsym;
			to = from + bin->dysymtab.nextdefsym;
			break;
		case 1:
			from = bin->dysymtab.ilocalsym;
			to = from + bin->dysymtab.nlocalsym;
			break;
#if NOT_USED
		case 2:
			from = bin->dysymtab.iundefsym;
			to = from + bin->dysymtab.nundefsym;
			break;
#endif
		}
		if (from == to) {
			continue;
		}

		from = R_MIN (from, symbols_size / sizeof (struct symbol_t));
		to = R_MIN (R_MIN (to, bin->nsymtab), symbols_size / sizeof (struct symbol_t));

		ut32 maxsymbols = symbols_size / sizeof (struct symbol_t);
		if (symbols_count >= maxsymbols) {
			symbols_count = maxsymbols - 1;
			eprintf ("macho warning: Symbol table truncated\n");
		}
		for (i = from; i < to && j < symbols_count; i++, j++) {
			RBinSymbol *sym = R_NEW0 (RBinSymbol);
			sym->vaddr = bin->symtab[i].n_value;
			sym->paddr = addr_to_offset (bin, sym->vaddr);
			symbols[j].size = 0;
			sym->bits = bin->symtab[i].n_desc & N_ARM_THUMB_DEF ? 16 : bits;

			if (bin->symtab[i].n_type & N_EXT) {
				sym->type = "EXT";
			} else {
				sym->type = "LOCAL";
			}
			int stridx = bin->symtab[i].n_strx;
			char *sym_name = get_name (bin, stridx, false);
			if (sym_name) {
				sym->name = sym_name;
				if (!bin->main_addr || bin->main_addr == UT64_MAX) {
					const char *name = sym->name;
					if (!strcmp (name, "__Dmain")) {
						bin->main_addr = symbols[j].addr;
					} else if (strstr (name, "4main") && !strstr (name, "STATIC")) {
						bin->main_addr = symbols[j].addr;
					} else if (!strcmp (name, "_main")) {
						bin->main_addr = symbols[j].addr;
					} else if (!strcmp (name, "main")) {
						bin->main_addr = symbols[j].addr;
					}
				}
			} else {
				sym->name = r_str_newf ("unk%u", (ut32)i);
			}
			if (!inSymtab (hash, sym->name, sym->vaddr)) {
				r_list_append (list, sym);
			} else {
				r_bin_symbol_free (sym);
			}
		}
	}
	to = R_MIN ((ut32)bin->nsymtab, bin->dysymtab.iundefsym + bin->dysymtab.nundefsym);
	for (i = bin->dysymtab.iundefsym; i < to; i++) {
		struct symbol_t symbol;
		if (j > symbols_count) {
			bprintf ("mach0-get-symbols: error\n");
			break;
		}
		if (parse_import_stub (bin, &symbol, i)) {
			j++;
			RBinSymbol *sym = R_NEW0 (RBinSymbol);
			sym->vaddr = symbol.addr;
			sym->paddr = symbol.offset;
			sym->name = symbol.name;
			if (!sym->name) {
				sym->name = r_str_newf ("unk%u", (ut32)i);
			}
			sym->is_imported = symbol.is_imported;
			r_list_append (list, sym);
		}
	}

	for (i = 0; i < bin->nsymtab && i < symbols_count; i++) {
		struct MACH0_(nlist) *st = &bin->symtab[i];


		int section = st->n_sect;
		if (section == 1 && j < symbols_count) {
			RBinSymbol *sym = R_NEW0(RBinSymbol);

			sym->vaddr = st->n_value;
			sym->paddr = addr_to_offset (bin, symbols[j].addr);
			sym->is_imported = symbols[j].is_imported;
			if (st->n_type & N_EXT) {
				sym->type = "EXT";
			} else {
				sym->type = "LOCAL";
			}
			char *sym_name = get_name (bin, st->n_strx, false);
			if (sym_name) {
				sym->name = sym_name;
				if (inSymtab (hash, sym->name, sym->vaddr)) {
					r_bin_symbol_free (sym);
					continue;
				}
				if (!bin->main_addr || bin->main_addr == UT64_MAX) {
					const char *name = sym->name;
					if (!strcmp (name, "__Dmain")) {
						bin->main_addr = symbols[i].addr;
					} else if (strstr (name, "4main") && !strstr (name, "STATIC")) {
						bin->main_addr = symbols[i].addr;
					} else if (!strcmp (symbols[i].name, "_main")) {
						bin->main_addr = symbols[i].addr;
					}
				}
			} else {
				sym->name = r_str_newf ("unk%u", (ut32)i);
			}
			r_list_append (list, sym);
			j++;
		}
	}
	ht_pp_free (hash);

    free (symbols);
	return list;
}
