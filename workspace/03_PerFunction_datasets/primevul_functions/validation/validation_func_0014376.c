static void cliprdr_write_file_contents_request(wStream* s,
                                                const CLIPRDR_FILE_CONTENTS_REQUEST* request)
{
	Stream_Write_UINT32(s, request->streamId);
	Stream_Write_UINT32(s, request->listIndex);
	Stream_Write_UINT32(s, request->dwFlags);
	Stream_Write_UINT32(s, request->nPositionLow);
	Stream_Write_UINT32(s, request->nPositionHigh);
	Stream_Write_UINT32(s, request->cbRequested);

	if (request->haveClipDataId)
		Stream_Write_UINT32(s, request->clipDataId);
}
