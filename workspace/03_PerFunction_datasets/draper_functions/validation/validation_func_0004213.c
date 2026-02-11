end_treaty(int withNationRecno,int newStatus)
{


	Nation* withNation = nation_array[withNationRecno];

	if( withNation->reputation > 0 )
	{
		int curStatus = get_relation_status(withNationRecno);

		if( curStatus == TALK_END_FRIENDLY_TREATY )
			change_reputation( -withNation->reputation * 10 / 100 );
		else
			change_reputation( -withNation->reputation * 20 / 100 );
	}


	if( newStatus <= NATION_NEUTRAL )
	{
		get_relation(withNationRecno)->good_relation_duration_rating = (float) 0;
		withNation->get_relation(nation_recno)->good_relation_duration_rating = (float) 0;
	}


	set_relation_status(withNationRecno, newStatus);


	if( withNationRecno == nation_array.player_recno )
		is_allied_with_player = 0;

	if( nation_recno == nation_array.player_recno )
		nation_array[withNationRecno]->is_allied_with_player = 0;
}
