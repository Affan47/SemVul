L3()
{register object *base=vs_base;
	register object *sup=base+VM3; VC3
	vs_check;
	{object V16;
	V16=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;{object V17;
	{register object V18;
	register object V19;
	V18= Cnil;
	V19= (((object)VV[3])->s.s_dbind);
	goto T32;
T32:;
	if(((V19))==Cnil){
	goto T35;}
	goto T34;
	goto T35;
T35:;
	goto T33;
	goto T34;
T34:;
	{register object V20;
	V20= CMPcar((V19));
	V18= (V20);}
	if(!(type_of((V18))==t_cons)){
	goto T40;}
	if(!((CMPcar((V18)))==((V16)))){
	goto T40;}
	V17= Ct;
	goto T30;
	goto T40;
T40:;
	V19= CMPcdr((V19));
	goto T32;
	goto T33;
T33:;
	V17= Cnil;
	goto T30;
	V17= Cnil;
	goto T30;}
	goto T30;
T30:;
	if(V17==Cnil)goto T29;
	base[1]= V17;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T29;
T29:;}
	{object V22;
	object V23;
	vs_base=vs_top;
	(void) (*Lnk90)();
	vs_top=sup;
	V22= vs_base[0];
	base[1]= V16;
	base[2]= STREF(object,(V22),64);
	vs_top=(vs_base=base+1)+2;
	Ladjoin();
	vs_top=sup;
	V23= vs_base[0];
	V24= Ct;
	STSET(object,(V22),64, (V23));
	base[1]= (V23);
	vs_top=(vs_base=base+1)+1;
	return;}
	}
}
