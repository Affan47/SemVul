LI4(V11,V12,V13)

object V11;object V12;object V13;
{	 VMB4 VMS4 VMV4
	bds_check;
	goto TTL;
TTL:;
	bds_bind(((object)VV[3]),((object)VV[2]));
	(void)((*(LnkLI58))());
	base[1]= Ct;
	base[2]= ((object)VV[10]);
	base[3]= (V11);
	base[4]= (V12);
	base[5]= (V13);
	vs_top=(vs_base=base+1)+5;
	Lformat();
	vs_top=sup;
	(((object)VV[5])->s.s_dbind)= immnum_plus((((object)VV[5])->s.s_dbind),small_fixnum(1));
	{frame_ptr fr;
	fr=frs_sch_catch(((object)VV[6]));
	if(fr==NULL) FEerror("The tag ~s is undefined.",1,((object)VV[6]));
	base[1]= ((object)VV[7]);
	vs_top=(vs_base=base+1)+1;
	unwind(fr,((object)VV[6]));}
	base[0]=base[0];
	return Cnil;
}
