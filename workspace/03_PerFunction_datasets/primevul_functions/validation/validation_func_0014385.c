UINT cliprdr_read_file_contents_request(wStream* s, CLIPRDR_FILE_CONTENTS_REQUEST* request)
{
	if (Stream_GetRemainingLength(s) < 24)
	{
		WLog_ERR(TAG, "not enough remaining data");
		return ERROR_INVALID_DATA;
	}

	request->haveClipDataId = FALSE;
	Stream_Read_UINT32(s, request->streamId);
	Stream_Read_UINT32(s, request->listIndex);
	Stream_Read_UINT32(s, request->dwFlags);
	Stream_Read_UINT32(s, request->nPositionLow);
	Stream_Read_UINT32(s, request->nPositionHigh);
	Stream_Read_UINT32(s, request->cbRequested);

	if (Stream_GetRemainingLength(s) >= 4)
	{
		Stream_Read_UINT32(s, request->clipDataId);
		request->haveClipDataId = TRUE;
	}

	if (!cliprdr_validate_file_contents_request(request))
		return ERROR_BAD_ARGUMENTS;

	return CHANNEL_RC_OK;
}
