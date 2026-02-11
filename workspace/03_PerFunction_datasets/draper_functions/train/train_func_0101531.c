csnset_update_csn(CSNSet **csnset, CSNType t, const CSN *csn)
{
	const CSNSet *f= csnset_get_csnset_node_from_type(*csnset, t);
	if(f==NULL)
	{
		csnset_add_csn(csnset,t,csn);
	}
	else
	{
		if (csn_compare(csn, (CSN*)(&f->csn)) > 0)
		{
			csn_init_by_csn((CSN*)(&f->csn),csn);
		}
	}
}
