void ntlm_decrypt_random_session_key(NTLM_CONTEXT* context)
{


	if (context->NegotiateKeyExchange)
		ntlm_rc4k(context->KeyExchangeKey, 16, context->EncryptedRandomSessionKey,
		          context->RandomSessionKey);
	else
		CopyMemory(context->RandomSessionKey, context->KeyExchangeKey, 16);
}
