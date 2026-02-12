BOOL security_mac_data(const BYTE* mac_salt_key, const BYTE* data, UINT32 length, BYTE* output)
{
	WINPR_DIGEST_CTX* sha1 = NULL;
	WINPR_DIGEST_CTX* md5 = NULL;
	BYTE length_le[4];
	BYTE sha1_digest[WINPR_SHA1_DIGEST_LENGTH];
	BOOL result = FALSE;

	security_UINT32_le(length_le, length);


	if (!(sha1 = winpr_Digest_New()))
		goto out;

	if (!winpr_Digest_Init(sha1, WINPR_MD_SHA1))
		goto out;

	if (!winpr_Digest_Update(sha1, mac_salt_key, 16))
		goto out;

	if (!winpr_Digest_Update(sha1, pad1, sizeof(pad1)))
		goto out;

	if (!winpr_Digest_Update(sha1, length_le, sizeof(length_le)))
		goto out;

	if (!winpr_Digest_Update(sha1, data, length))
		goto out;

	if (!winpr_Digest_Final(sha1, sha1_digest, sizeof(sha1_digest)))
		goto out;


	if (!(md5 = winpr_Digest_New()))
		goto out;


	if (!winpr_Digest_Init_Allow_FIPS(md5, WINPR_MD_MD5))
		goto out;

	if (!winpr_Digest_Update(md5, mac_salt_key, 16))
		goto out;

	if (!winpr_Digest_Update(md5, pad2, sizeof(pad2)))
		goto out;

	if (!winpr_Digest_Update(md5, sha1_digest, sizeof(sha1_digest)))
		goto out;

	if (!winpr_Digest_Final(md5, output, WINPR_MD5_DIGEST_LENGTH))
		goto out;

	result = TRUE;
out:
	winpr_Digest_Free(sha1);
	winpr_Digest_Free(md5);
	return result;
}
