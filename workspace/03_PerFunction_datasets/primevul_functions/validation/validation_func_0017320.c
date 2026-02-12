int ntlm_compute_lm_v2_response(NTLM_CONTEXT* context)
{
	BYTE* response;
	BYTE value[WINPR_MD5_DIGEST_LENGTH];

	if (context->LmCompatibilityLevel < 2)
	{
		if (!sspi_SecBufferAlloc(&context->LmChallengeResponse, 24))
			return -1;

		ZeroMemory(context->LmChallengeResponse.pvBuffer, 24);
		return 1;
	}


	if (ntlm_compute_ntlm_v2_hash(context, context->NtlmV2Hash) < 0)
		return -1;


	CopyMemory(value, context->ServerChallenge, 8);
	CopyMemory(&value[8], context->ClientChallenge, 8);

	if (!sspi_SecBufferAlloc(&context->LmChallengeResponse, 24))
		return -1;

	response = (BYTE*)context->LmChallengeResponse.pvBuffer;

	winpr_HMAC(WINPR_MD_MD5, (void*)context->NtlmV2Hash, WINPR_MD5_DIGEST_LENGTH, (BYTE*)value,
	           WINPR_MD5_DIGEST_LENGTH, (BYTE*)response, WINPR_MD5_DIGEST_LENGTH);


	CopyMemory(&response[16], context->ClientChallenge, 8);
	return 1;
}
