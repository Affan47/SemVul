fqOpUUBitOR(
	FQATOM *	pLValue,
	FQATOM *	pRValue,
	FQATOM *	pResult)
{
	if (isNativeNum( pLValue->eType) && isNativeNum( pRValue->eType))
	{
		pResult->val.ui32Val = pLValue->val.ui32Val | pRValue->val.ui32Val;
		pResult->eType = FLM_UINT32_VAL;
	}
	else
	{
		pResult->val.ui64Val =
			fqGetUInt64( pLValue) | fqGetUInt64( pRValue);
		pResult->eType = FLM_UINT64_VAL;
	}
}
