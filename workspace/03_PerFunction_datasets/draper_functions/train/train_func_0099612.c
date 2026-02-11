ai_reset_defense_mode()
{
	if(ai_status!=CAMP_IN_DEFENSE)
		return;


	DefenseUnit *defPtr = defense_array;
	Unit	*unitPtr;
	int	found=0;

	for(int i=0; i<=MAX_WORKER; i++, defPtr++)
	{
		if(!defPtr->unit_recno)
			continue;

		if(unit_array.is_deleted(defPtr->unit_recno))
			continue;

		unitPtr = unit_array[defPtr->unit_recno];
		if(unitPtr->nation_recno==nation_recno && unitPtr->action_misc==ACTION_MISC_DEFENSE_CAMP_RECNO &&
			unitPtr->action_misc_para==firm_recno)
			found++;
	}

	if(!found)
	{
		set_employ_worker(1);
		memset(defense_array, 0, sizeof(DefenseUnit)*(MAX_WORKER+1));
	}
}
