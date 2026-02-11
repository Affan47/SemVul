init_player_reply(int talkToNationRecno)
{
	nation_report_mode = NATION_REPORT_TALK;

	info.player_reply_mode = 1;


	int nationCount = nation_filter();

	int i;
	for( i=1 ; i<=nationCount ; i++ )
	{
		if( nation_filter(i) == talkToNationRecno )
		{
			browse_nation_recno = i;
			break;
		}
	}

	err_when( i>nationCount );


	if( sys.view_mode == MODE_NATION )
		browse_nation.refresh(browse_nation_recno);
}
