Oct6100ApiReleaseTsiMemEntry(
				IN OUT	tPOCT6100_INSTANCE_API		f_pApiInstance,
				IN		UINT16						f_usTsiMemIndex )
{
	tPOCT6100_SHARED_INFO		pSharedInfo;
	PVOID	pTsiMemAlloc;
	UINT32	ulResult;
	UINT32	ulIndex;


	pSharedInfo = f_pApiInstance->pSharedInfo;


	if ( f_usTsiMemIndex > cOCT6100_TSST_CONTROL_TIMESTAMP_BASE_ENTRY )
		ulIndex = f_usTsiMemIndex - cOCT6100_TSI_MEM_FOR_TIMESTAMP;
	else
		ulIndex = f_usTsiMemIndex;


	if ( ulIndex > cOCT6100_TSST_CONTROL_PHASING_TSST_BASE_ENTRY )
		ulIndex -= pSharedInfo->ChipConfig.usMaxPhasingTssts;

	mOCT6100_GET_TSI_MEMORY_ALLOC_PNT( pSharedInfo, pTsiMemAlloc )

	ulResult = OctapiLlmAllocDealloc( pTsiMemAlloc, ulIndex );
	if ( ulResult != cOCT6100_ERR_OK )
	{
		return cOCT6100_ERR_FATAL_93;
	}

	return cOCT6100_ERR_OK;
}
