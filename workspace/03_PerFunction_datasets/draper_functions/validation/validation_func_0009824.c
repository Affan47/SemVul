total_spy_skill_level(int spyPlace, int spyPlacePara, int spyNationRecno, int& spyCount)
{
	int  totalSpyLevel=0;
	Spy* spyPtr;

	spyCount = 0;

	for( int i=spy_array.size() ; i>0 ; i-- )
	{
		if( spy_array.is_deleted(i) )
			continue;

		spyPtr = spy_array[i];

		if( spyPtr->true_nation_recno != spyNationRecno )
			continue;

		if( spyPtr->spy_place != spyPlace )
			continue;

		if( spyPtr->spy_place_para != spyPlacePara )
			continue;

		spyCount++;

		totalSpyLevel += spyPtr->spy_skill;
	}

	return totalSpyLevel;
}
