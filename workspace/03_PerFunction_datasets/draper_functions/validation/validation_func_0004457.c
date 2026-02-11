ssl3_handshake_mac(SSL *s, int md_nid,
	     const char *sender, int len, unsigned char *p)
	{
	unsigned int ret;
	int npad,n;
	unsigned int i;
	unsigned char md_buf[EVP_MAX_MD_SIZE];
	EVP_MD_CTX ctx,*d=NULL;

	if (s->s3->handshake_buffer)
		if (!ssl3_digest_cached_records(s))
			return 0;


	for (i=0;i<SSL_MAX_DIGEST;i++)
		{
		  if (s->s3->handshake_dgst[i]&&EVP_MD_CTX_type(s->s3->handshake_dgst[i])==md_nid)
		  	{
		  	d=s->s3->handshake_dgst[i];
			break;
			}
		}
	if (!d) {
		SSLerr(SSL_F_SSL3_HANDSHAKE_MAC,SSL_R_NO_REQUIRED_DIGEST);
		return 0;
	}
	EVP_MD_CTX_init(&ctx);
	EVP_MD_CTX_set_flags(&ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
	EVP_MD_CTX_copy_ex(&ctx,d);
	n=EVP_MD_CTX_size(&ctx);
	if (n < 0)
		return 0;

	npad=(48/n)*n;
	if (sender != NULL)
		EVP_DigestUpdate(&ctx,sender,len);
	EVP_DigestUpdate(&ctx,s->session->master_key,
		s->session->master_key_length);
	EVP_DigestUpdate(&ctx,ssl3_pad_1,npad);
	EVP_DigestFinal_ex(&ctx,md_buf,&i);

	EVP_DigestInit_ex(&ctx,EVP_MD_CTX_md(&ctx), NULL);
	EVP_DigestUpdate(&ctx,s->session->master_key,
		s->session->master_key_length);
	EVP_DigestUpdate(&ctx,ssl3_pad_2,npad);
	EVP_DigestUpdate(&ctx,md_buf,i);
	EVP_DigestFinal_ex(&ctx,p,&ret);

	EVP_MD_CTX_cleanup(&ctx);

	return((int)ret);
	}
