hud_escort_ship_hit(object *objp, int quadrant)
{
	int num, i;
	shield_hit_info	*shi;


	if(MULTI_DOGFIGHT){
		return;
	}

	for ( i = 0; i < Num_escort_ships; i++ ) {
		if ( Escort_ships[i].objnum == OBJ_INDEX(objp) ) {
			shi = &Escort_ships[i].hit_info;

			hud_gauge_popup_start(HUD_ESCORT_VIEW);
			if ( quadrant >= 0 ) {


				num = Quadrant_xlate[quadrant];
				shi->shield_hit_timers[num] = timestamp(SHIELD_HIT_DURATION);
			} else {
				shi->shield_hit_timers[HULL_HIT_OFFSET] = timestamp(SHIELD_HIT_DURATION);
			}
		}
	}
}
