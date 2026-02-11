pdf_authenticate_user_password(pdf_crypt *crypt, unsigned char *password, int pwlen)
{
	unsigned char output[32];
	pdf_compute_user_password(crypt, password, pwlen, output);
	if (crypt->r == 2 || crypt->r == 5 || crypt->r == 6)
		return memcmp(output, crypt->u, 32) == 0;
	if (crypt->r == 3 || crypt->r == 4)
		return memcmp(output, crypt->u, 16) == 0;
	return 0;
}
