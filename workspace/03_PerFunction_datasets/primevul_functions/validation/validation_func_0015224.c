BOOL license_read_scope_list(wStream* s, SCOPE_LIST* scopeList)
{
	UINT32 i;
	UINT32 scopeCount;

	if (Stream_GetRemainingLength(s) < 4)
		return FALSE;

	Stream_Read_UINT32(s, scopeCount);

	if (scopeCount > Stream_GetRemainingLength(s) / 4)
		return FALSE;

	scopeList->count = scopeCount;
	scopeList->array = (LICENSE_BLOB*)calloc(scopeCount, sizeof(LICENSE_BLOB));
	if (!scopeList->array)
		return FALSE;


	for (i = 0; i < scopeCount; i++)
	{
		scopeList->array[i].type = BB_SCOPE_BLOB;

		if (!license_read_binary_blob(s, &scopeList->array[i]))
			return FALSE;
	}

	return TRUE;
}
