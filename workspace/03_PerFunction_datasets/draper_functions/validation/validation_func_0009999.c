L1()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	{object V1;
	V1=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (V1);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk48)();
	vs_top=sup;
	V4= vs_base[0];
	{object V2;
	object V3= V4;
	if(V3==Cnil){
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	base[1]=V2=MMcons(Cnil,Cnil);
	goto T1;
T1:;
	base[3]= (V3->c.c_car);
	vs_top=(vs_base=base+3)+1;
	Lint_char();
	vs_top=sup;
	V6= vs_base[0];
	base[2]= coerce_to_string(V6);
	vs_top=(vs_base=base+2)+1;
	Lintern();
	vs_top=sup;
	(V2->c.c_car)= vs_base[0];
	if((V3=MMcdr(V3))==Cnil){
	vs_top=(vs_base=base+1)+1;
	return;}
	V2=MMcdr(V2)=MMcons(Cnil,Cnil);
	goto T1;}
	}
}
