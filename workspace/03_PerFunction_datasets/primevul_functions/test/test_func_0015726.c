static int trimDynamic (dynamicPtr * dp)
{

	if (!dp->freeOK) {
		return FALSE;
	}
	return gdReallocDynamic(dp, dp->logicalSize);
}
