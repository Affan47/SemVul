LI9__WT_SYMBOL_FUNCTION__cmpspecial(V79)

object V79;
{	 VMB9 VMS9 VMV9
	goto TTL;
TTL:;
	if(((((object)VV[46])->s.s_dbind))==Cnil){
	goto T167;}
	princ_str("symbol_function(",((object)VV[47]));
	base[0]= (V79);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk76)();
	vs_top=sup;
	V80= vs_base[0];
	(void)((*(LnkLI75))(V80));
	princ_char(41,((object)VV[47]));
	{object V81 = Cnil;
	VMR9(V81)}
	goto T167;
T167:;
	princ_char(40,((object)VV[47]));
	base[0]= (V79);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk76)();
	vs_top=sup;
	V82= vs_base[0];
	(void)((*(LnkLI75))(V82));
	princ_str("->s.s_gfdef)",((object)VV[47]));
	{object V83 = Cnil;
	VMR9(V83)}
	base[0]=base[0];
	return Cnil;
}
