internal_EvictByKeySlot(TCPA_KEY_HANDLE slot)
{
	TCPA_RESULT result;
	UINT32 paramSize;
	UINT64 offset;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering Evict Key");

#ifdef TSS_BUILD_TSS12
	if (TPM_VERSION_IS(1,2)) {
		LogDebugFn("Evicting key using FlushSpecific for TPM 1.2");

		return TCSP_FlushSpecific_Common(slot, TPM_RT_KEY);
	}
#endif

	offset = 10;
	LoadBlob_UINT32(&offset, slot, txBlob);
	LoadBlob_Header(TPM_TAG_RQU_COMMAND, offset, TPM_ORD_EvictKey, txBlob);

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	result = UnloadBlob_Header(txBlob, &paramSize);

	LogResult("Evict Key", result);
	return result;
}
