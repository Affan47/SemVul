decode(len) int len; {
    unsigned int a, a7, b8;

    rpt = 0;
    while (len-- > 0) {
	a = *rdatap++;
	if (rptflg) {
	    if (a == rptq) {
		if (len-- < 1) {
		    if (debug) fprintf(db,"decode rpt error A\n");
		    return(-1);
		}
		rpt = xunchar(*rdatap++);
		if (len-- < 1) {
		    if (debug) fprintf(db,"decode rpt error B\n");
		    return(-1);
		}
		a = *rdatap++;
	    }
	}
	b8 = 0;
	if (ebqflg) {
	    if (a == ebq) {
		b8 = 128;
		if (len-- < 1) {
		    if (debug) fprintf(db,"decode ebq error\n");
		    return(-1);
		}
		a = *rdatap++;
	    }
	}
        if (a == rctlq) {
	    if (len-- < 1) {
		if (debug) fprintf(db,"decode ctl error\n");
		return(-1);
	    }
            a = *rdatap++;
            a7 = a & 127;
            if (a7 > 62 && a7 < 96)
                a = ctl(a);
        }
        if (rpt == 0)
	  rpt = 1;
	a |= b8;
	a &= 0xff;


	if (text && a == CR)
	  continue;
	for (; rpt > 0; rpt--) {
	    if (osp) {
		*osp++ = a;
	    } else {
		putc((char)a,ofp);
		if (ferror(ofp)) {
		    if (debug)
		      fprintf(db,"decode putc a=%u errno=%u\n",a,errno);
		    failure = 1;
		    return(-1);
		}
	    }
	}
    }
    return(0);
}
