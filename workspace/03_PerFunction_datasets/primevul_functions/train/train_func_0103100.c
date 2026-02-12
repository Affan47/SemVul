static BOOL security_salted_hash(const BYTE* salt, const BYTE* input, int length, const BYTE* salt1,
                                 const BYTE* salt2, BYTE* output)
{
	WINPR_DIGEST_CTX* sha1 = NULL;
	WINPR_DIGEST_CTX* md5 = NULL;
	BYTE sha1_digest[WINPR_SHA1_DIGEST_LENGTH];
	BOOL result = FALSE;


	if (!(sha1 = winpr_Digest_New()))
		goto out;

	if (!winpr_Digest_Init(sha1, WINPR_MD_SHA1))
		goto out;

	if (!winpr_Digest_Update(sha1, input, length))
		goto out;

	if (!winpr_Digest_Update(sha1, salt, 48))
		goto out;

	if (!winpr_Digest_Update(sha1, salt1, 32))
		goto out;

	if (!winpr_Digest_Update(sha1, salt2, 32))
		goto out;

	if (!winpr_Digest_Final(sha1, sha1_digest, sizeof(sha1_digest)))
		goto out;


	if (!(md5 = winpr_Digest_New()))
		goto out;


	if (!winpr_Digest_Init_Allow_FIPS(md5, WINPR_MD_MD5))
		goto out;

	if (!winpr_Digest_Update(md5, salt, 48))
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
