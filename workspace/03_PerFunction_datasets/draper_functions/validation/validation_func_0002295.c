putchr(int ac)
{
	char *lp;
	int c;
	Rune rune;

	lp = linp;
	c = ac;
	if(listf) {
		if(c == '\n') {
			if(linp != line && linp[-1] == ' ') {
				*lp++ = '\\';
				*lp++ = 'n';
			}
		} else {
			if(col > (72-6-2)) {
				col = 8;
				*lp++ = '\\';
				*lp++ = '\n';
				*lp++ = '\t';
			}
			col++;
			if(c=='\b' || c=='\t' || c=='\\') {
				*lp++ = '\\';
				if(c == '\b')
					c = 'b';
				else
				if(c == '\t')
					c = 't';
				col++;
			} else
			if(c<' ' || c>='\177') {
				*lp++ = '\\';
				*lp++ = 'x';
				*lp++ =  hex[c>>12];
				*lp++ =  hex[c>>8&0xF];
				*lp++ =  hex[c>>4&0xF];
				c     =  hex[c&0xF];
				col += 5;
			}
		}
	}

	rune = c;
	lp += runetochar(lp, &rune);

	if(c == '\n' || lp >= &line[sizeof(line)-5]) {
		linp = line;
		write(oflag? 2: 1, line, lp-line);
		return;
	}
	linp = lp;
}
