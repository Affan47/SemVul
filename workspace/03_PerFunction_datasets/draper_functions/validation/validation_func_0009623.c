certify_cert(X509 **xret, char *infile, EVP_PKEY *pkey, X509 *x509,
	     const EVP_MD *dgst, STACK_OF(OPENSSL_STRING) *sigopts,
	     STACK_OF(CONF_VALUE) *policy, CA_DB *db,
	     BIGNUM *serial, char *subj, unsigned long chtype, int multirdn, int email_dn, char *startdate, char *enddate,
	     long days, int batch, char *ext_sect, CONF *lconf, int verbose,
	     unsigned long certopt, unsigned long nameopt, int default_op,
	     int ext_copy, ENGINE *e)
	{
	X509 *req=NULL;
	X509_REQ *rreq=NULL;
	EVP_PKEY *pktmp=NULL;
	int ok= -1,i;

	if ((req=load_cert(bio_err, infile, FORMAT_PEM, NULL, e, infile)) == NULL)
		goto err;
	if (verbose)
		X509_print(bio_err,req);

	BIO_printf(bio_err,"Check that the request matches the signature\n");

	if ((pktmp=X509_get_pubkey(req)) == NULL)
		{
		BIO_printf(bio_err,"error unpacking public key\n");
		goto err;
		}
	i=X509_verify(req,pktmp);
	EVP_PKEY_free(pktmp);
	if (i < 0)
		{
		ok=0;
		BIO_printf(bio_err,"Signature verification problems....\n");
		goto err;
		}
	if (i == 0)
		{
		ok=0;
		BIO_printf(bio_err,"Signature did not match the certificate\n");
		goto err;
		}
	else
		BIO_printf(bio_err,"Signature ok\n");

	if ((rreq=X509_to_X509_REQ(req,NULL,EVP_md5())) == NULL)
		goto err;

	ok=do_body(xret,pkey,x509,dgst,sigopts,policy,db,serial,subj,chtype,multirdn,email_dn,startdate,enddate,
		days,batch,verbose,rreq,ext_sect,lconf, certopt, nameopt, default_op,
		ext_copy, 0);

err:
	if (rreq != NULL) X509_REQ_free(rreq);
	if (req != NULL) X509_free(req);
	return(ok);
	}
