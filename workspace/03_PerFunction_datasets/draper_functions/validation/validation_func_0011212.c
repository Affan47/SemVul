L1()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	{object V1;
	object V2;
	V1=(base[0]);
	V2=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V3;
	register object V4;
	register object V5;
	V3= Cnil;
	V4= Cnil;
	V5= Cnil;
	V3= Cnil;
	{object V6;
	V6= ((V2))->v.v_self[(long)9];
	V4= (
	V7 = CMPcar((V6)),
	(type_of(V7) == t_sfun ?(*((V7)->sfn.sfn_self)):
	(fcall.argd=2,type_of(V7)==t_vfun) ?
	(*((V7)->sfn.sfn_self)):
	(fcall.fun=(V7),fcalln))((V1),CMPcdr((V6))));}
	{object V8;
	V8= ((V2))->v.v_self[(long)10];
	V5= (
	V9 = CMPcar((V8)),
	(type_of(V9) == t_sfun ?(*((V9)->sfn.sfn_self)):
	(fcall.argd=2,type_of(V9)==t_vfun) ?
	(*((V9)->sfn.sfn_self)):
	(fcall.fun=(V9),fcalln))((V1),CMPcdr((V8))));}
	goto T6;
T6:;
	if(!(immnum_gt((V4),(V5)))){
	goto T13;}
	goto T7;
	goto T13;
T13:;
	V3= make_cons((V4),(V3));
	goto T16;
	goto T16;
T16:;
	V4= immnum_plus((V4),small_fixnum(1));
	goto T6;
	goto T7;
T7:;
	base[2]= (*(LnkLI3))((V3));
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	}
}
