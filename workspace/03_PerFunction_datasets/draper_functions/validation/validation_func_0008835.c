multi_ts_get_team_and_slot(char *ship_name,int *team_index,int *slot_index, bool mantis2757switch)
{
	int idx;


	*team_index = -1;
	*slot_index = -1;


	if(Netgame.type_flags & NG_TYPE_TEAM){
		Assert(MAX_TVT_WINGS == MULTI_TS_MAX_TVT_TEAMS);
		for (idx = 0; idx < MAX_TVT_WINGS; idx++) {

			if ( !strnicmp(ship_name, TVT_wing_names[idx], strlen(TVT_wing_names[idx])) && multi_ts_validate_ship(ship_name, TVT_wing_names[idx]) ) {
				*team_index = idx;
				*slot_index = (ship_name[strlen(ship_name)-1] - '1');


				Assert( (*slot_index >= 0) && (*slot_index < MAX_WSS_SLOTS) );
			}
		}
	}

	else {
		int wing, ship;
		for (idx = 0; idx < MAX_STARTING_WINGS; idx++) {

			if ( !strnicmp(ship_name, Starting_wing_names[idx], strlen(Starting_wing_names[idx])) && multi_ts_validate_ship(ship_name, Starting_wing_names[idx]) ) {
				wing = idx;
				ship = (ship_name[strlen(ship_name)-1] - '1');


				Assert( (ship >= 0) && (ship < MULTI_TS_NUM_SHIP_SLOTS_TEAM) );


				*team_index = 0;
				*slot_index = wing * MULTI_TS_NUM_SHIP_SLOTS_TEAM + ship;
			}
		}
	}
	if(mantis2757switch)
		Assert((*team_index != -1) && (*slot_index != -1));
}
