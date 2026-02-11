L6()
{register object *base=vs_base;
	register object *sup=base+VM6; VC6
	vs_reserve(VM6);
	{object V15;
	check_arg(1);
	V15=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= list(3,((object)VV[15]),small_fixnum(0),one_minus((V15)));
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
