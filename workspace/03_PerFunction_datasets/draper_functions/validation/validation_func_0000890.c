RPC_CMK_ConvertMigration(TSS_HCONTEXT hContext,
			 TCS_KEY_HANDLE hParentHandle,
			 TPM_CMK_AUTH restrictTicket,
			 TPM_HMAC sigTicket,
			 UINT32 keyDataSize,
			 BYTE *keyData,
			 UINT32 msaListSize,
			 BYTE *msaList,
			 UINT32 randomSize,
			 BYTE *random,
			 TPM_AUTH *pAuth,
			 UINT32 *outDataSize,
			 BYTE **outData)
{
	TSS_RESULT result = (TSS_E_INTERNAL_ERROR | TSS_LAYER_TSP);
	struct host_table_entry *entry = get_table_entry(hContext);

	if (entry == NULL)
		return TSPERR(TSS_E_NO_CONNECTION);

	switch (entry->type) {
		case CONNECTION_TYPE_TCP_PERSISTANT:
			result = RPC_CMK_ConvertMigration_TP(entry, hParentHandle, restrictTicket,
					sigTicket, keyDataSize, keyData, msaListSize, msaList,
					randomSize, random, pAuth, outDataSize, outData);
			break;
		default:
			break;
	}

	put_table_entry(entry);

	return result;
}
