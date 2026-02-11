tcs_wrap_DSAP(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	UINT16 entityType;
	TCS_KEY_HANDLE keyHandle;
	TPM_NONCE nonceOddDSAP, nonceEven, nonceEvenDSAP;
	UINT32 entityValueSize;
	BYTE *entityValue;
	TCS_AUTHHANDLE authHandle;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	if ((result = ctx_verify_context(hContext)))
		goto done;

	LogDebugFn("thread %ld context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_UINT16, 1, &entityType, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_UINT32, 2, &keyHandle, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_NONCE, 3, &nonceOddDSAP, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_UINT32, 4, &entityValueSize, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	entityValue = malloc(entityValueSize);
	if (entityValue == NULL) {
		LogError("malloc of %u bytes failed.", entityValueSize);
		return TCSERR(TSS_E_OUTOFMEMORY);
	}
	if (getData(TCSD_PACKET_TYPE_PBYTE, 5, entityValue, entityValueSize, &data->comm)) {
		free(entityValue);
		return TCSERR(TSS_E_INTERNAL_ERROR);
	}

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_DSAP_Internal(hContext, entityType, keyHandle, &nonceOddDSAP, entityValueSize,
				    entityValue, &authHandle, &nonceEven, &nonceEvenDSAP);

	MUTEX_UNLOCK(tcsp_lock);
	free(entityValue);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 3);

		if (setData(TCSD_PACKET_TYPE_UINT32, 0, &authHandle, 0, &data->comm))
			return TCSERR(TSS_E_INTERNAL_ERROR);
		if (setData(TCSD_PACKET_TYPE_NONCE, 1, &nonceEven, 0, &data->comm))
			return TCSERR(TSS_E_INTERNAL_ERROR);
		if (setData(TCSD_PACKET_TYPE_NONCE, 2, &nonceEvenDSAP, 0, &data->comm))
			return TCSERR(TSS_E_INTERNAL_ERROR);
	} else
done:		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}
