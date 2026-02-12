void ContentLine_Analyzer::SkipBytesAfterThisLine(int64_t length)
	{


	if ( last_char == '\r' )
		skip_pending = length;
	else
		SkipBytes(length);
	}
