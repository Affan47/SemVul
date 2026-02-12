void ntlm_encrypt_random_session_key(NTLM_CONTEXT* context)
{


	ntlm_rc4k(context->KeyExchangeKey, 16, context->RandomSessionKey,
	          context->EncryptedRandomSessionKey);
}
