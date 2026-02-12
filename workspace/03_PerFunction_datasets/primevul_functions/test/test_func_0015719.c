static int appendDynamic (dynamicPtr * dp, const void *src, int size)
{
	int bytesNeeded;
	char *tmp;

	if (!dp->dataGood) {
		return FALSE;
	}


	bytesNeeded = dp->pos + size;

	if (bytesNeeded > dp->realSize) {

		if (!dp->freeOK) {
			return FALSE;
		}
		gdReallocDynamic(dp, bytesNeeded * 2);
	}


	tmp = (char *) dp->data;
	memcpy((void *) (tmp + (dp->pos)), src, size);
	dp->pos += size;

	if (dp->pos > dp->logicalSize) {
		dp->logicalSize = dp->pos;
	}

	return TRUE;
}
