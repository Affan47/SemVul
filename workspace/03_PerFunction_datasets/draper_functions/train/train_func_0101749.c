TCSP_PhysicalEnable_Internal(TCS_CONTEXT_HANDLE hContext)
{
	UINT64 offset = 0;
	TSS_RESULT result;
	UINT32 paramSize;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering Physical Enable");
	if ((result = ctx_verify_context(hContext)))
		return result;

	if ((result = tpm_rqu_build(TPM_ORD_PhysicalEnable, &offset, txBlob, NULL)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	result = UnloadBlob_Header(txBlob, &paramSize);
	LogResult("Physical Enable", result);

	return result;
}
