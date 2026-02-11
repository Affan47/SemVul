Transport_FlushSpecific(TSS_HCONTEXT tspContext,
			TCS_HANDLE hResHandle,
			TPM_RESOURCE_TYPE resourceType)
{
	UINT64 offset;
	TSS_RESULT result;
	UINT32 handlesLen = 1;
	TCS_HANDLE *handles, handle;
	BYTE data[sizeof(UINT32)];

	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	handle = hResHandle;
	handles = &handle;

	offset = 0;
	Trspi_LoadBlob_UINT32(&offset, resourceType, data);

	result = obj_context_transport_execute(tspContext, TPM_ORD_FlushSpecific, sizeof(data),
					       data, NULL, &handlesLen, &handles, NULL, NULL, NULL,
					       NULL);

	return result;
}
