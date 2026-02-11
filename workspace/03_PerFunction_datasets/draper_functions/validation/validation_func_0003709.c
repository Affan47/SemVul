epat_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

	r = regr + cont_map[cont];

	switch (pi->mode) {

	case 0:	w0(r); w2(1); w2(3);
		a = r1(); w2(4); b = r1();
		return j44(a,b);

	case 1: w0(0x40+r); w2(1); w2(4);
		a = r1(); b = r2(); w0(0xff);
		return j53(a,b);

	case 2: w0(0x20+r); w2(1); w2(0x25);
		a = r0(); w2(4);
		return a;

	case 3:
	case 4:
	case 5: w3(r); w2(0x24); a = r4(); w2(4);
		return a;

	}
	return -1;
}
