L46()
{register object *base=vs_base;
	register object *sup=base+VM46; VC46
	vs_check;
	{object V263;
	V263=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((V263))==Cnil){
	goto T1039;}
	base[1]= CMPcar((V263));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk244)();
	vs_top=sup;
	goto T1039;
T1039:;
	base[1]= (V263);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
