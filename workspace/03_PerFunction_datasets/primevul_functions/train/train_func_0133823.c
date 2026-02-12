void IRC_Analyzer::StartTLS()
	{


	starttls = true;

	RemoveSupportAnalyzer(cl_orig);
	RemoveSupportAnalyzer(cl_resp);

	Analyzer* ssl = analyzer_mgr->InstantiateAnalyzer("SSL", Conn());
	if ( ssl )
		AddChildAnalyzer(ssl);

	val_list* vl = new val_list;
	vl->append(BuildConnVal());

	ConnectionEvent(irc_starttls, vl);
	}
