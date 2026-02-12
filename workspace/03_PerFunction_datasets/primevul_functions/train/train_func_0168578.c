void tls_fips_digest_extra(
	const EVP_CIPHER_CTX *cipher_ctx, EVP_MD_CTX *mac_ctx,
	const unsigned char *data, size_t data_len, size_t orig_len)
	{
	size_t block_size, digest_pad, blocks_data, blocks_orig;
	if (EVP_CIPHER_CTX_mode(cipher_ctx) != EVP_CIPH_CBC_MODE)
		return;
	block_size = EVP_MD_CTX_block_size(mac_ctx);


	digest_pad = block_size == 64 ? 21 : 29;
	blocks_orig = (orig_len + digest_pad)/block_size;
	blocks_data = (data_len + digest_pad)/block_size;


	EVP_DigestSignUpdate(mac_ctx, data,
				(blocks_orig - blocks_data + 1) * block_size);
	}
