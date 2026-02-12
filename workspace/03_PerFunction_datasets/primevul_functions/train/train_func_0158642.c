void ContentLine_Analyzer::CheckNUL()
	{


	TCP_Analyzer* tcp =
		static_cast<TCP_ApplicationAnalyzer*>(Parent())->TCP();

	if ( tcp )
		{
		TCP_Endpoint* endp = IsOrig() ? tcp->Orig() : tcp->Resp();
		if ( endp->state == TCP_ENDPOINT_PARTIAL &&
		     endp->LastSeq() - endp->StartSeq() <= 2 )
			;
		else
			{
			if ( ! suppress_weirds && Conn()->FlagEvent(NUL_IN_LINE) )
				Conn()->Weird("NUL_in_line");
			flag_NULs = 0;
			}
		}
	}
