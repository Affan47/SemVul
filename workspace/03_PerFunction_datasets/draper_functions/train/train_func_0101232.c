DumpStringMap ( const XMP_StringMap & map, XMP_StringPtr label, XMP_TextOutputProc outProc, void * refCon )
{
	XMP_Status			status;
	XMP_cStringMapPos	currPos;
	XMP_cStringMapPos	endPos = map.end();

	size_t maxLen = 0;
	for ( currPos = map.begin(); currPos != endPos; ++currPos ) {
		size_t currLen = currPos->first.size();
		if ( currLen > maxLen ) maxLen = currLen;
	}

	OutProcNewline();
	OutProcLiteral ( label );
	OutProcNewline();

	for ( currPos = map.begin(); currPos != endPos; ++currPos ) {
		OutProcNChars ( "  ", 2 );
		DumpClearString ( currPos->first, outProc, refCon );
		OutProcPadding ( maxLen - currPos->first.size() );
		OutProcNChars ( " => ", 4 );
		DumpClearString ( currPos->second, outProc, refCon );
		OutProcNewline();
	}

EXIT:
	return status;

}
