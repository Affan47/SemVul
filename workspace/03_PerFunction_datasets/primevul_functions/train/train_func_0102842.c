fmtptr(void *value, PrintfTarget *target)
{
	int			vallen;
	char		convert[64];


	vallen = sprintf(convert, "%p", value);

	dostr(convert, vallen, target);
}
