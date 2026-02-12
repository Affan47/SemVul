static BOOL cliprdr_validate_file_contents_request(const CLIPRDR_FILE_CONTENTS_REQUEST* request)
{


	if (request->dwFlags & FILECONTENTS_SIZE)
	{
		if (request->cbRequested != sizeof(UINT64))
		{
			WLog_ERR(TAG, "[%s]: cbRequested must be %" PRIu32 ", got %" PRIu32 "", __FUNCTION__,
			         sizeof(UINT64), request->cbRequested);
			return FALSE;
		}

		if (request->nPositionHigh != 0 || request->nPositionLow != 0)
		{
			WLog_ERR(TAG, "[%s]: nPositionHigh and nPositionLow must be set to 0", __FUNCTION__);
			return FALSE;
		}
	}

	return TRUE;
}
