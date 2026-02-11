radius_setmppekeys2(VALUE_PAIR *vp, REQUEST_INFO *req_info)
{
    int i;
    MD5_CTX Context;
    u_char  *salt = vp->strvalue;
    u_char  *crypt = vp->strvalue + 2;
    u_char  plain[32];
    u_char  buf[MD5_HASH_SIZE];
    char    *type = "Send";

    if (vp->attribute == PW_MS_MPPE_RECV_KEY)
	type = "Recv";

    if (vp->lvalue != 34) {
	error("RADIUS: Incorrect attribute length (%d) for MS-MPPE-%s-Key",
	      vp->lvalue, type);
	return -1;
    }

    if ((salt[0] & 0x80) == 0) {
	error("RADIUS: Illegal salt value for MS-MPPE-%s-Key attribute", type);
	return -1;
    }

    memcpy(plain, crypt, 32);

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, req_info->request_vector, AUTH_VECTOR_LEN);
    MD5_Update(&Context, salt, 2);
    MD5_Final(buf, &Context);

    for (i = 0; i < 16; i++)
	plain[i] ^= buf[i];

    if (plain[0] != sizeof(mppe_send_key) ) {
	error("RADIUS: Incorrect key length (%d) for MS-MPPE-%s-Key attribute",
	      (int) plain[0], type);
	return -1;
    }

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, crypt, 16);
    MD5_Final(buf, &Context);

    plain[16] ^= buf[0];

    if (vp->attribute == PW_MS_MPPE_SEND_KEY)
	memcpy(mppe_send_key, plain + 1, 16);
    else
	memcpy(mppe_recv_key, plain + 1, 16);

    return 0;
}
