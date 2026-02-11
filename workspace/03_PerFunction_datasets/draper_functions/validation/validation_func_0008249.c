MattributeAvail(
	MAP *m,
	CSF_ATTR_ID id)
{
	ATTR_CNTRL_BLOCK b;

     	if (! CsfIsValidMap(m))
	 	return 0;
	return(CsfGetAttrBlock(m, id, &b) != 0);
}
