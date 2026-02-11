SetMVcellRepr(
	CSF_CR cellRepr,
	void *c)
{
	switch (cellRepr)
	{
		case CR_INT1  : *((INT1 *)c) = MV_INT1;
				break;
		case CR_INT2  : *((INT2 *)c) = MV_INT2;
				break;
		case CR_INT4  : *((INT4 *)c) = MV_INT4;
				break;
		case CR_UINT1 : *((UINT1 *)c) = MV_UINT1;
				break;
		case CR_UINT2 : *((UINT2 *)c) = MV_UINT2;
				break;
		case CR_REAL8 :
				((UINT4 *)c)[1] = MV_UINT4;
		default       : POSTCOND(
					cellRepr == CR_REAL8 ||
					cellRepr == CR_REAL4 ||
					cellRepr == CR_UINT4 );
				*((UINT4 *)c) = MV_UINT4;
	}
}
