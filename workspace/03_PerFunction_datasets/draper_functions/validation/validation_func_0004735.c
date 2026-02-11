QCC_InitData (void)
{
	static char parmname[12][MAX_PARMS];
	static temp_t ret_temp;
	int		i;

	qcc_sourcefile = NULL;

	numstatements = 1;
	strofs = 1;
	numfunctions = 1;
	numglobaldefs = 1;
	numfielddefs = 1;

	memset(&ret_temp, 0, sizeof(ret_temp));

	def_ret.ofs = OFS_RETURN;
	def_ret.name = "return";
	def_ret.temp = &ret_temp;
	def_ret.constant = false;
	def_ret.type	= NULL;
	ret_temp.ofs = def_ret.ofs;
	ret_temp.scope = NULL;
	ret_temp.size = 3;
	ret_temp.next = NULL;
	for (i=0 ; i<MAX_PARMS ; i++)
	{
		def_parms[i].temp = NULL;
		def_parms[i].type = NULL;
		def_parms[i].ofs = OFS_PARM0 + 3*i;
		def_parms[i].name = parmname[i];
		sprintf(parmname[i], "parm%i", i);
	}
}
