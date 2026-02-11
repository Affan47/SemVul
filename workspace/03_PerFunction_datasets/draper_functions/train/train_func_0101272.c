L9()
{register object *base=vs_base;
	register object *sup=base+VM9; VC9
	vs_check;
	{object V64;
	V64=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= ((object)VV[3]);
	vs_top=(vs_base=base+1)+1;
	Lfloat_digits();
	return;
	}
}
