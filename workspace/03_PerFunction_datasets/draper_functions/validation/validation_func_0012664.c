find_selected_type( short *selectedRecno)
{
	short dummyId;
	if( selectedRecno == NULL)
		selectedRecno = &dummyId;

	if( unit_array.selected_recno )
	{


		if( unit_array.selected_count == 1)
		{
			Unit *unitPtr = unit_array[*selectedRecno = unit_array.selected_recno];
			return unitPtr->nation_recno == nation_array.player_recno ?
				SCREEN_OBJECT_FRIEND_UNIT :
				(unitPtr->true_nation_recno() == nation_array.player_recno ?
				SCREEN_OBJECT_SPY_UNIT : SCREEN_OBJECT_ENEMY_UNIT);
		}


		if( unit_array.selected_count > 1)
		{
			*selectedRecno = unit_array.selected_recno;
			return SCREEN_OBJECT_UNIT_GROUP;
		}
	}


	if( firm_array.selected_recno )
	{
		Firm *firmPtr = firm_array[*selectedRecno = firm_array.selected_recno];
		return firmPtr->nation_recno == nation_array.player_recno ?
			SCREEN_OBJECT_FRIEND_FIRM : SCREEN_OBJECT_ENEMY_FIRM;
	}


	if( town_array.selected_recno )
	{
		Town *townPtr = town_array[*selectedRecno = town_array.selected_recno];
		return townPtr->nation_recno == nation_array.player_recno ?
			SCREEN_OBJECT_FRIEND_TOWN : SCREEN_OBJECT_ENEMY_TOWN;
	}


	if( site_array.selected_recno )
	{
		Site *sitePtr = site_array[*selectedRecno = site_array.selected_recno];
		return SCREEN_OBJECT_SITE;
	}


	if( wall_res.selected_x_loc >= 0 && wall_res.selected_y_loc >= 0)
	{
		*selectedRecno = world.get_loc(wall_res.selected_x_loc, wall_res.selected_y_loc)->power_nation_recno;
		return SCREEN_OBJECT_WALL;
	}

	return SCREEN_OBJECT_NONE;
}
