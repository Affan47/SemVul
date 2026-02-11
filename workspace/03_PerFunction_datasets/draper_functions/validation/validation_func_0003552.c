LI10__GET_NODE_INDEX__info(V121,V122)

register object V121;object V122;
{	 VMB10 VMS10 VMV10
	bds_check;
	goto TTL;
TTL:;
	{object V123;
	V123= (V121);
	bds_bind(((object)VV[9]),Cnil);
	if(((V122))!=Cnil){
	goto T292;}
	{long V124 = (long)0;
	bds_unwind1;
	VMR10((object)V124)}
	goto T292;
T292:;
	base[1]= ((object)VV[23]);
	base[2]= (*(LnkLI101))((V121));
	base[3]= ((object)VV[24]);
	vs_top=(vs_base=base+1)+3;
	(void) (*Lnk102)();
	vs_top=sup;
	V121= vs_base[0];
	{long V125= fix((VFUN_NARGS=2,(*(LnkLI94))((V121),(V122),small_fixnum(0))));
	if(!((V125)>=((long)0))){
	goto T300;}}
	{long V126= (long)(*(LnkLI97))((long)1);
	{long V127 = (long)(*(LnkLI96))((V122),V126);
	bds_unwind1;
	VMR10((object)V127)}}
	goto T300;
T300:;
	base[1]= ((object)VV[25]);
	base[2]= (V123);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk99)();
	vs_top=sup;
	{long V128 = (long)0;
	bds_unwind1;
	VMR10((object)V128)}}
	base[0]=base[0];
}
