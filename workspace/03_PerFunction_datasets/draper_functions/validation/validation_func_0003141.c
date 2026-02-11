regatom(int* flagp) {
	register char *ret;
	int flags;

	*flagp = WORST;

	switch (*regparse++) {
	case '^':
		ret = regnode(BOL);
		break;
	case '$':
		ret = regnode(EOL);
		break;
	case '.':
		ret = regnode(ANY);
		*flagp |= HASWIDTH|SIMPLE;
		break;
	case '[': {
			register int classbeg;
			register int classend;

			if (*regparse == '^') {
				ret = regnode(ANYBUT);
				regparse++;
			} else
				ret = regnode(ANYOF);
			if (*regparse == ']' || *regparse == '-')
				regc(*regparse++);
			while (*regparse != '\0' && *regparse != ']') {
				if (*regparse == '-') {
					regparse++;
					if (*regparse == ']' || *regparse == '\0')
						regc('-');
					else {
						classbeg = UCHARAT(regparse-2)+1;
						classend = UCHARAT(regparse);
						if (classbeg > classend+1)
							FAIL("invalid [] range");
						for (; classbeg <= classend; classbeg++)
							regc(classbeg);
						regparse++;
					}
				} else
					regc(*regparse++);
			}
			regc('\0');
			if (*regparse != ']')
				FAIL("unmatched []");
			regparse++;
			*flagp |= HASWIDTH|SIMPLE;
		}
		break;
	case '\0':
	case '|':
		FAIL("internal urp");
		break;
	case '?':
	case '+':
	case '*':
		FAIL("?+* follows nothing");
		break;
	case '\\':
		if (*regparse == '\0')
			FAIL("trailing \\");
		if (*regparse == '(') {
			regparse++;
			ret = reg(1, &flags);
			if (ret == nil)
				return(nil);
			*flagp |= flags&(HASWIDTH|SPSTART);
		} else {
			ret = regnode(EXACTLY);
			regc(*regparse++);
			regc('\0');
			*flagp |= HASWIDTH|SIMPLE;
		}
		break;
	default: {
			register int len;
			register char ender;

			regparse--;
			len = strcspn(regparse, META);
			if (len <= 0)
				FAIL("internal disaster");
			ender = *(regparse+len);
			if (len > 1 && ISMULT(ender))
				len--;
			*flagp |= HASWIDTH;
			if (len == 1)
				*flagp |= SIMPLE;
			ret = regnode(EXACTLY);
			while (len > 0) {
				regc(*regparse++);
				len--;
			}
			regc('\0');
		}
		break;
	}

	return(ret);
}
