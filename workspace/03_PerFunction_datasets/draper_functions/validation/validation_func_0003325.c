new_rule(GROUP *gp, ITEM *lhs, ITEM *rhs, int line)
{
	RULE *rp;


	switch(ITEM_TYPE(*lhs))
	{
	case ITEM_MATCH:
		if(count_items(lhs) == 1)
		{
			gp->match = rhs;
			gp->mrlen = count_items(rhs);
			check_rhs(gp->match,gp->mrlen,gp,line);
		}
		else
		{
			kmflcomp_error(line,"'match' must be the only item on the input side of a rule");
		}
		return NULL;
	case ITEM_NOMATCH:
		if(count_items(lhs) == 1)
		{
			gp->nomatch = rhs;
			gp->nmrlen = count_items(rhs);
			check_rhs(gp->nomatch,gp->nmrlen,gp,line);
		}
		else
		{
			kmflcomp_error(line,"'nomatch' must be the only item on the input side of a rule");
		}
		return NULL;
	}


	rp = (RULE *)checked_alloc(sizeof(RULE),1);
	rp->lhs = lhs;
	rp->rhs = rhs;
	rp->ilen = count_items(rp->lhs);
	rp->olen = count_items(rp->rhs);
	rp->next = NULL;
	rp->line = line;


	check_rule(rp,gp);
	return rp;
}
