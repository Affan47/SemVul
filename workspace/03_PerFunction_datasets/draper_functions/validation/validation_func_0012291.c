L46()
{register object *base=vs_base;
	register object *sup=base+VM46; VC46
	vs_check;
	{object V163;
	object V164;
	object V165;
	V163=(base[0]);
	V164=(base[1]);
	V165=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[3]= (V163);
	base[4]= (V164);
	vs_top=(vs_base=base+3)+2;
	(void) (*Lnk16)();
	return;
	}
}
