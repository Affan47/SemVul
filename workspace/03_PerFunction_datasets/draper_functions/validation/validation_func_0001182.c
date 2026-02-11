move_to_now_with_filter(int destX, int destY, short* selectedUnitArray, int selectedCount)
{
	int destRegionId = world.get_loc(destX, destY)->region_id;
	Unit *unitPtr = operator[](selectedUnitArray[0]);


	if(unitPtr->mobile_type==UNIT_AIR)
	{
		move_to_now(destX, destY, selectedUnitArray, selectedCount);
		return;
	}


	int arraySize = sizeof(short)*selectedCount;
	filtered_unit_array = (short*) mem_add(arraySize);
	filtering_unit_array = (short*) mem_add(arraySize);
	memcpy(filtering_unit_array, selectedUnitArray, arraySize);
	filtering_unit_count = selectedCount;

	int unprocessCount = selectedCount;
	int filterRegionId = destRegionId;
	int filterDestX = destX, filterDestY = destY;
	int loopCount, filteringCount, i;


	for(loopCount=0; loopCount<=unprocessCount; loopCount++)
	{
		memset(filtered_unit_array, 0, arraySize);
		filtered_unit_count = 0;
		filteringCount = filtering_unit_count;
		filtering_unit_count = 0;


		for(i=0; i<filteringCount; i++)
		{
			unitPtr = operator[](filtering_unit_array[i]);
			if(world.get_loc(unitPtr->next_x_loc(), unitPtr->next_y_loc())->region_id==filterRegionId)
				filtered_unit_array[filtered_unit_count++] = filtering_unit_array[i];
			else
				filtering_unit_array[filtering_unit_count++] = filtering_unit_array[i];
		}


		if(filtered_unit_count)
			move_to_now(filterDestX, filterDestY, filtered_unit_array, filtered_unit_count);

		if(!filtering_unit_count)
			break;


		unitPtr = operator[](filtering_unit_array[0]);
		filterRegionId = world.get_loc(unitPtr->next_x_loc(), unitPtr->next_y_loc())->region_id;
		filterDestX = destX;
		filterDestY = destY;
		unitPtr->different_territory_destination(filterDestX, filterDestY);
	}

	mem_del(filtered_unit_array);
	mem_del(filtering_unit_array);
}
