assign_to_camp(int destX, int destY, char remoteAction, short* selectedUnitArray, int selectedCount)
{
	divide_array(destX, destY, selectedUnitArray, selectedCount);

	if(selected_land_unit_count)
	{
		int assignCount=0, moveCount=0;
		short *assignArray = (short*) mem_add(sizeof(short)*selected_land_unit_count);
		short *moveArray = (short*) mem_add(sizeof(short)*selected_land_unit_count);
		char unitClass;
		Unit *unitPtr;
		memset(assignArray, 0, sizeof(short)*selected_land_unit_count);
		memset(moveArray, 0, sizeof(short)*selected_land_unit_count);


		for(int i=0; i<selectedCount; i++)
		{
			err_when(unit_array.is_deleted(selectedUnitArray[i]));
			unitPtr = operator[](selectedUnitArray[i]);
			unitClass = unit_res[unitPtr->unit_id]->unit_class;
			if(unitClass==UNIT_CLASS_HUMAN || unitClass==UNIT_CLASS_WEAPON)
				assignArray[assignCount++] = selectedUnitArray[i];
			else
				moveArray[moveCount++] = selectedUnitArray[i];
		}

		if(assignCount)
			assign(destX, destY, 1, remoteAction, assignArray, assignCount);
		if(moveCount)
			move_to(destX, destY, 1, moveArray, moveCount, remoteAction);

		mem_del(assignArray);
		mem_del(moveArray);
	}

	if(selected_sea_unit_count)
		ship_to_beach(destX, destY, 1, selected_sea_unit_array, selected_sea_unit_count, remoteAction);

	if(selected_air_unit_count)
		move_to(destX, destY, 1, selected_air_unit_array, selected_air_unit_count, remoteAction);


	selected_land_unit_count = selected_sea_unit_count = selected_air_unit_count = 0;
	mem_del(selected_land_unit_array);
	mem_del(selected_sea_unit_array);
	mem_del(selected_air_unit_array);
}
