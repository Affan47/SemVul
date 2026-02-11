decrease_recharge_rate(object* obj, SYSTEM_TYPE ship_system)
{
	int	*lose_index=NULL, *gain_index1=NULL, *gain_index2=NULL, *tmp=NULL;
	int	count;
	ship	*ship_p = &Ships[obj->instance];

	if (ship_p->flags2 & SF2_NO_ETS)
		return;

	switch ( ship_system ) {
		case WEAPONS:
			if ( !ship_has_energy_weapons(ship_p) )
				return;

			lose_index = &ship_p->weapon_recharge_index;

			if ( obj->flags & OF_NO_SHIELDS )
				gain_index1 = NULL;
			else
				gain_index1 = &ship_p->shield_recharge_index;

			if ( !ship_has_engine_power(ship_p) )
				gain_index2 = NULL;
			else
				gain_index2 = &ship_p->engine_recharge_index;

			break;

		case SHIELDS:
			if ( obj->flags & OF_NO_SHIELDS )
				return;

			lose_index = &ship_p->shield_recharge_index;

			if ( !ship_has_energy_weapons(ship_p) )
				gain_index1 = NULL;
			else
				gain_index1 = &ship_p->weapon_recharge_index;

			if ( !ship_has_engine_power(ship_p) )
				gain_index2 = NULL;
			else
				gain_index2 = &ship_p->engine_recharge_index;

			break;

		case ENGINES:
			if ( !ship_has_engine_power(ship_p) )
				return;

			lose_index = &ship_p->engine_recharge_index;

			if ( !ship_has_energy_weapons(ship_p) )
				gain_index1 = NULL;
			else
				gain_index1 = &ship_p->weapon_recharge_index;

			if ( obj->flags & OF_NO_SHIELDS )
				gain_index2 = NULL;
			else
				gain_index2 = &ship_p->shield_recharge_index;

			break;

	}


	if (!gain_index1 && !gain_index2)
		return;


	count = MIN(2, *lose_index);
	if ( count <= 0 ) {
		if ( obj == Player_obj ) {
			snd_play( &Snds[SND_ENERGY_TRANS_FAIL], 0.0f );
		}
		return;
	}

	*lose_index -= count;


	if ( gain_index1 && gain_index2 ) {
		if ( *gain_index1 > *gain_index2 ) {
			tmp = gain_index1;
			gain_index1 = gain_index2;
			gain_index2 = tmp;
		}
	}

	int sanity=0;
	while(count > 0) {
		if ( gain_index1 && *gain_index1 < MAX_ENERGY_INDEX ) {
			*gain_index1 += 1;
			count--;
		}

		if ( count <= 0 )
			break;

		if ( gain_index2 && *gain_index2 < MAX_ENERGY_INDEX ) {
			*gain_index2 += 1;
			count--;
		}

		if ( sanity++ > 10 ) {
			Int3();
			break;
		}
	}

	if ( obj == Player_obj )
		snd_play( &Snds[SND_ENERGY_TRANS], 0.0f );
}
