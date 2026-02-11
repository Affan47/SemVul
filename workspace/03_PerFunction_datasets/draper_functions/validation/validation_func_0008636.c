popctl(Void)
{
	if( ctlstack-- < ctls )
		Fatal("control stack empty");
	--blklevel;
}
