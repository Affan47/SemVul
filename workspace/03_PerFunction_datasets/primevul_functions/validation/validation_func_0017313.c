void ntlm_generate_client_challenge(NTLM_CONTEXT* context)
{

	if (memcmp(context->ClientChallenge, NTLM_NULL_BUFFER, 8) == 0)
		winpr_RAND(context->ClientChallenge, 8);
}
