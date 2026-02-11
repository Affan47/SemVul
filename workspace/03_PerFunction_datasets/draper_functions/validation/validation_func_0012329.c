L20()
{register object *base=vs_base;
	register object *sup=base+VM20; VC20
	vs_check;
	{object V105;
	V105=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((V105))==Cnil){
	goto T268;}
	V106= CMPcar(CMPcddddr(CMPcar((V105))));
	base[1]= CMPcdr((V105));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk41)();
	vs_top=sup;
	V107= vs_base[0];
	base[1]= append(V106,V107);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T268;
T268:;
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
