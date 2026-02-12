crypto_update_taichange(void)
{
	static const u_int len = 3 * sizeof(u_int32);


	if (sign_digest == NULL || sign_pkey == NULL)
		return;


	if (tai_leap.ptr == NULL || ntohl(tai_leap.vallen) != len)
		return;


	crypto_update();
}
