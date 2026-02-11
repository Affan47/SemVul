Oct6100ApiWriteToneDetectEvent(
				IN OUT	tPOCT6100_INSTANCE_API					f_pApiInstance,
				IN		UINT32									f_ulChannelIndex,
				IN		UINT32									f_ulToneEventNumber,

				IN		UINT32									f_ulExtToneChanIndex )
{
	tPOCT6100_SHARED_INFO			pSharedInfo;
	tOCT6100_WRITE_PARAMS			WriteParams;
	tOCT6100_READ_PARAMS			ReadParams;
	UINT32	ulResult;
	UINT16	usReadData;


	pSharedInfo = f_pApiInstance->pSharedInfo;


	ReadParams.pProcessContext = f_pApiInstance->pProcessContext;

	ReadParams.ulUserChipId = pSharedInfo->ChipConfig.ulUserChipId;
	ReadParams.pusReadData = &usReadData;

	WriteParams.pProcessContext = f_pApiInstance->pProcessContext;

	WriteParams.ulUserChipId = pSharedInfo->ChipConfig.ulUserChipId;


	ReadParams.ulReadAddress  = pSharedInfo->MemoryMap.ulChanMainMemBase + ( f_ulChannelIndex * pSharedInfo->MemoryMap.ulChanMainMemSize );
	ReadParams.ulReadAddress += cOCT6100_CH_MAIN_TONE_EVENT_OFFSET;
	ReadParams.ulReadAddress += (f_ulToneEventNumber / 16) * 2;

	mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;


	WriteParams.ulWriteAddress  = ReadParams.ulReadAddress;
	WriteParams.usWriteData  = usReadData;
	WriteParams.usWriteData |= ( 0x1 << ( 15 - ( f_ulToneEventNumber % 16 )));

	mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;


	if ( f_ulExtToneChanIndex != cOCT6100_INVALID_INDEX )
	{

		ReadParams.ulReadAddress  = pSharedInfo->MemoryMap.ulChanMainMemBase + ( f_ulExtToneChanIndex * pSharedInfo->MemoryMap.ulChanMainMemSize );
		ReadParams.ulReadAddress += cOCT6100_CH_MAIN_TONE_EVENT_OFFSET;
		ReadParams.ulReadAddress += (f_ulToneEventNumber / 16) * 2;

		mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;


		WriteParams.ulWriteAddress  = ReadParams.ulReadAddress;
		WriteParams.usWriteData  = usReadData;
		WriteParams.usWriteData |= ( 0x1 << ( 15 - ( f_ulToneEventNumber % 16 )));

		mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;
	}


	return cOCT6100_ERR_OK;
}
