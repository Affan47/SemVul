static void cliprdr_write_file_contents_response(wStream* s,
                                                 const CLIPRDR_FILE_CONTENTS_RESPONSE* response)
{
	Stream_Write_UINT32(s, response->streamId);
	Stream_Write(s, response->requestedData, response->cbRequested);
}
