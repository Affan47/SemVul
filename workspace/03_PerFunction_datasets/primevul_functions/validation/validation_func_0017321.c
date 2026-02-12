void ntlm_generate_key_exchange_key(NTLM_CONTEXT* context)
{

	CopyMemory(context->KeyExchangeKey, context->SessionBaseKey, 16);
}
