detect_detail()
{
	switch( info.nation_report_mode )
	{
		case NATION_REPORT_INFO:
			detect_nation_info();
			break;

		case NATION_REPORT_TALK:
			detect_nation_talk();
			break;

		case NATION_REPORT_CHAT:
			detect_nation_chat();
			break;

		case NATION_REPORT_TALK_LOG:
			if( browse_talk_msg.detect() )
				info.browse_talk_msg_recno = browse_talk_msg.recno();
			break;
	}
}
