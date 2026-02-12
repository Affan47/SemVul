bool AES_GCM_DecryptContext::Decrypt(
	const void *pEncryptedDataAndTag, size_t cbEncryptedDataAndTag,
	const void *pIV,
	void *pPlaintextData, uint32 *pcbPlaintextData,
	const void *pAdditionalAuthenticationData, size_t cbAuthenticationData
) {

	if ( cbEncryptedDataAndTag > *pcbPlaintextData + crypto_aead_aes256gcm_ABYTES )
	{
		*pcbPlaintextData = 0;
		return false;
	}

    unsigned long long cbPlaintextData_longlong;
    const int nDecryptResult = crypto_aead_aes256gcm_decrypt_afternm(
		static_cast<unsigned char*>( pPlaintextData ), &cbPlaintextData_longlong,
		nullptr,
		static_cast<const unsigned char*>( pEncryptedDataAndTag ), cbEncryptedDataAndTag,
		static_cast<const unsigned char*>( pAdditionalAuthenticationData ), cbAuthenticationData,
		static_cast<const unsigned char*>( pIV ), static_cast<const crypto_aead_aes256gcm_state*>( m_ctx )
	);

    *pcbPlaintextData = cbPlaintextData_longlong;

    return nDecryptResult == 0;
}
