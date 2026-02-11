rotating_submodel_has_ship_subsys(int submodel, ship *shipp)
{
	model_subsystem	*psub;
	ship_subsys			*pss;

	int found = 0;


	for ( pss = GET_FIRST(&shipp->subsys_list); pss != END_OF_LIST(&shipp->subsys_list); pss = GET_NEXT(pss) ) {
		psub = pss->system_info;
		if (psub->subobj_num == submodel) {
			found = 1;
			break;
		}
	}

	return found;
}
