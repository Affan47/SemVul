process(FilterChar * & start, FilterChar * & stop)
  {
    buf.clear();
    FilterChar * i = start;
    while (i != stop)
    {
      if (*i == '&') {
	FilterChar * i0 = i;
	FilterChar::Chr chr;
	++i;
	if (i != stop && *i == '#') {
	  chr = 0;
	  ++i;
	  while (i != stop && asc_isdigit(*i)) {
	    chr *= 10;
	    chr += *i - '0';
	    ++i;
	  }
	} else {
	  while (i != stop && (asc_isalpha(*i) || asc_isdigit(*i))) {
	    ++i;
	  }
	  chr = '?';
	}
	if (i != stop && *i == ';')
	  ++i;
	buf.append(FilterChar(chr, i0, i));
      } else {
	buf.append(*i);
	++i;
      }
    }
    buf.append('\0');
    start = buf.pbegin();
    stop  = buf.pend() - 1;
  }
