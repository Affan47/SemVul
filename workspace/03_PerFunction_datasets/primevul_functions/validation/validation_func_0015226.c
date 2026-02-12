BOOL license_read_binary_blob(wStream* s, LICENSE_BLOB* blob)
{
	UINT16 wBlobType;

	if (Stream_GetRemainingLength(s) < 4)
		return FALSE;

	Stream_Read_UINT16(s, wBlobType);
	Stream_Read_UINT16(s, blob->length);

	if (Stream_GetRemainingLength(s) < blob->length)
		return FALSE;


	if ((blob->type != BB_ANY_BLOB) && (blob->length == 0))
		return TRUE;

	if ((blob->type != wBlobType) && (blob->type != BB_ANY_BLOB))
	{
		WLog_ERR(TAG,
		         "license binary blob type (0x%" PRIx16 ") does not match expected type (0x%" PRIx16
		         ").",
		         wBlobType, blob->type);
	}

	blob->type = wBlobType;
	blob->data = (BYTE*)malloc(blob->length);
	if (!blob->data)
		return FALSE;
	Stream_Read(s, blob->data, blob->length);
	return TRUE;
}
