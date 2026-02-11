comm_read_regr( PIA *pi, int cont, int regr )

{       int     l, h, r;

        r = regr + cont_map[cont];

        switch (pi->mode)  {

        case 0: w0(r); P1; w0(0);
        	w2(6); l = r1(); w0(0x80); h = r1(); w2(4);
                return j44(l,h);

        case 1: w0(r+0x20); P1;
        	w0(0); w2(0x26); h = r0(); w2(4);
                return h;

	case 2:
	case 3:
        case 4: w3(r+0x20); (void)r1();
        	w2(0x24); h = r4(); w2(4);
                return h;

        }
        return -1;
}
