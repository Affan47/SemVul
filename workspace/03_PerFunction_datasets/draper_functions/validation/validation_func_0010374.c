L23__WINDOW_SYNC__dwtrans()
{register object *base=vs_base;
	register object *sup=base+VM23; VC23
	vs_check;
	{object V54;
	V54=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (((object)VV[5])->s.s_dbind);
	base[2]= small_fixnum(1);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk215)();
	return;
	}
}
