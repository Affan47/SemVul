match(struct magic_set *ms, struct magic *magic, uint32_t nmagic,
    const struct buffer *b, size_t offset, int mode, int text,
    int flip, uint16_t *indir_count, uint16_t *name_count,
    int *printed_something, int *need_separator, int *returnval,
    int *found_match)
{
	uint32_t magindex = 0;
	unsigned int cont_level = 0;
	int found_matchv = 0;
	int returnvalv = 0, e;
	int firstline = 1;
	struct buffer bb;
	int print = (ms->flags & MAGIC_NODESC) == 0;


	if (returnval == NULL)
		returnval = &returnvalv;
	if (found_match == NULL)
		found_match = &found_matchv;

	if (file_check_mem(ms, cont_level) == -1)
		return -1;

	for (magindex = 0; magindex < nmagic; magindex++) {
		int flush = 0;
		struct magic *m = &magic[magindex];

		if (m->type != FILE_NAME)
		if ((IS_STRING(m->type) &&
#define FLT (STRING_BINTEST | STRING_TEXTTEST)
		     ((text && (m->str_flags & FLT) == STRING_BINTEST) ||
		      (!text && (m->str_flags & FLT) == STRING_TEXTTEST))) ||
		    (m->flag & mode) != mode) {
flush:

			while (magindex < nmagic - 1 &&
			    magic[magindex + 1].cont_level != 0)
				magindex++;
			cont_level = 0;
			continue;
		}

		if (msetoffset(ms, m, &bb, b, offset, cont_level) == -1)
			goto flush;
		ms->line = m->lineno;


		switch (mget(ms, m, b, CAST(const unsigned char *, bb.fbuf),
		    bb.flen, offset, cont_level,
		    mode, text, flip, indir_count, name_count,
		    printed_something, need_separator, returnval, found_match))
		{
		case -1:
			return -1;
		case 0:
			flush = m->reln != '!';
			break;
		default:
			if (m->type == FILE_INDIRECT) {
				*found_match = 1;
				*returnval = 1;
			}

			switch (magiccheck(ms, m)) {
			case -1:
				return -1;
			case 0:
				flush++;
				break;
			default:
				flush = 0;
				break;
			}
			break;
		}
		if (flush) {


			goto flush;
		}

		if (*m->desc)
			*found_match = 1;

		if ((e = handle_annotation(ms, m, firstline)) != 0)
		{
			*need_separator = 1;
			*printed_something = 1;
			*returnval = 1;
			return e;
		}


		if (print && *m->desc) {
			*need_separator = 1;
			*printed_something = 1;
			*returnval = 1;
			if (print_sep(ms, firstline) == -1)
				return -1;
			if (mprint(ms, m) == -1)
				return -1;
		}

		switch (moffset(ms, m, &bb, &ms->c.li[cont_level].off)) {
		case -1:
		case 0:
			goto flush;
		default:
			break;
		}


		if (file_check_mem(ms, ++cont_level) == -1)
			return -1;

		while (magindex + 1 < nmagic &&
		    magic[magindex + 1].cont_level != 0) {
			m = &magic[++magindex];
			ms->line = m->lineno;

			if (cont_level < m->cont_level)
				continue;
			if (cont_level > m->cont_level) {


				cont_level = m->cont_level;
			}
			if (msetoffset(ms, m, &bb, b, offset, cont_level) == -1)
				goto flush;
			if (m->flag & OFFADD) {
				ms->offset +=
				    ms->c.li[cont_level - 1].off;
			}

#ifdef ENABLE_CONDITIONALS
			if (m->cond == COND_ELSE ||
			    m->cond == COND_ELIF) {
				if (ms->c.li[cont_level].last_match == 1)
					continue;
			}
#endif
			switch (mget(ms, m, b, CAST(const unsigned char *,
			    bb.fbuf), bb.flen, offset,
			    cont_level, mode, text, flip, indir_count,
			    name_count, printed_something, need_separator,
			    returnval, found_match)) {
			case -1:
				return -1;
			case 0:
				if (m->reln != '!')
					continue;
				flush = 1;
				break;
			default:
				if (m->type == FILE_INDIRECT) {
					*found_match = 1;
					*returnval = 1;
				}
				flush = 0;
				break;
			}

			switch (flush ? 1 : magiccheck(ms, m)) {
			case -1:
				return -1;
			case 0:
#ifdef ENABLE_CONDITIONALS
				ms->c.li[cont_level].last_match = 0;
#endif
				break;
			default:
#ifdef ENABLE_CONDITIONALS
				ms->c.li[cont_level].last_match = 1;
#endif
				if (m->type == FILE_CLEAR)
					ms->c.li[cont_level].got_match = 0;
				else if (ms->c.li[cont_level].got_match) {
					if (m->type == FILE_DEFAULT)
						break;
				} else
					ms->c.li[cont_level].got_match = 1;

				if (*m->desc)
					*found_match = 1;

				if ((e = handle_annotation(ms, m, firstline))
				    != 0) {
					*need_separator = 1;
					*printed_something = 1;
					*returnval = 1;
					return e;
				}
				if (print && *m->desc) {


					if (!*printed_something) {
						*printed_something = 1;
						if (print_sep(ms, firstline)
						    == -1)
							return -1;
					}

					if (*need_separator
					    && (m->flag & NOSPACE) == 0) {
						if (file_printf(ms, " ") == -1)
							return -1;
					}
					*returnval = 1;
					*need_separator = 0;
					if (mprint(ms, m) == -1)
						return -1;
					*need_separator = 1;
				}

				switch (moffset(ms, m, &bb,
				    &ms->c.li[cont_level].off)) {
				case -1:
				case 0:
					flush = 1;
					cont_level--;
					break;
				default:
					break;
				}


				if (file_check_mem(ms, ++cont_level) == -1)
					return -1;
				break;
			}
		}
		if (*printed_something) {
			firstline = 0;
		}
		if ((ms->flags & MAGIC_CONTINUE) == 0 && *found_match) {
			return *returnval;
		}
		cont_level = 0;
	}
	return *returnval;
}
