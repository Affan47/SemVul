search_or_wait()
{
	#define	SQUARE1	9
	#define	SQUARE2	25
	#define	SQUARE3	49
	#define	DIMENSION 7

	int curXLoc = next_x_loc(), curYLoc = next_y_loc();
	short surrArray[SQUARE3];
	int xShift, yShift, checkXLoc, checkYLoc, hasFree, i, shouldWait;
	short unitRecno;
	Unit *unitPtr;
	Location *locPtr;


	memset(surrArray, 0, sizeof(short)*SQUARE3);
	for(shouldWait=0, hasFree=0, i=2; i<=SQUARE3; i++)
	{
		if(i==SQUARE1 || i==SQUARE2 || i==SQUARE3)
		{
			if(!hasFree)
			{
				shouldWait++;
				break;
			}
			else
				hasFree = 0;
		}

		misc.cal_move_around_a_point(i, DIMENSION, DIMENSION, xShift, yShift);
		checkXLoc = curXLoc+xShift;
		checkYLoc = curYLoc+yShift;
		if(checkXLoc<0 || checkXLoc>=MAX_WORLD_X_LOC || checkYLoc<0 || checkYLoc>=MAX_WORLD_Y_LOC)
			continue;

		locPtr = world.get_loc(checkXLoc, checkYLoc);
		if(!locPtr->has_unit(mobile_type))
		{
			hasFree++;
			continue;
		}

		unitRecno = locPtr->unit_recno(mobile_type);
		err_when(!unitRecno);
		if(unit_array.is_deleted(unitRecno))
			continue;

		unitPtr = unit_array[unitRecno];
		if(unitPtr->nation_recno==nation_recno && unitPtr->unit_group_id==unit_group_id &&
			((unitPtr->cur_action==SPRITE_WAIT && unitPtr->waiting_term>1) || unitPtr->cur_action==SPRITE_TURN ||
			  unitPtr->cur_action==SPRITE_MOVE))
		{
			surrArray[i-2] = unitRecno;
			unitPtr->unit_group_id++;
		}
	}


	if(!shouldWait)
		search(move_to_x_loc, move_to_y_loc, 1, SEARCH_MODE_IN_A_GROUP);


	for(i=0; i<SQUARE3; i++)
	{
		if(surrArray[i])
		{
			err_when(unit_array.is_deleted(surrArray[i]));
			unitPtr = unit_array[surrArray[i]];
			unitPtr->unit_group_id--;
		}
	}

	if(shouldWait)
		set_wait();
}
