L10()
{register object *base=vs_base;
	register object *sup=base+VM10; VC10
	vs_check;
	{register object V26;
	V26=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if((CMPcdr((V26)))!=Cnil){
	goto T110;}
	base[1]= list(2,((object)VV[32]),CMPcar((V26)));
	vs_top=(vs_base=base+1)+1;
	return;
	goto T110;
T110:;
	V27= list(3,((object)VV[7]),((object)VV[33]),list(2,((object)VV[32]),CMPcar((V26))));
	base[1]= CMPcdr((V26));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk57)();
	vs_top=sup;
	V28= vs_base[0];
	base[1]= list(3,((object)VV[7]),V27,V28);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
