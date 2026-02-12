crypto_setup(void)
{
	struct pkey_info *pinfo;
	char	filename[MAXFILENAME];
	char	hostname[MAXFILENAME];
	char	*randfile;
	char	statstr[NTP_MAXSTRLEN];
	l_fp	seed;
	u_int	len;
	int	bytes;
	u_char	*ptr;


	if (crypto_flags & CRYPTO_FLAG_ENAB) {
		msyslog(LOG_NOTICE,
		    "crypto_setup: spurious crypto command");
		return;
	}
	ssl_check_version();


	if (!RAND_status()) {
		if (rand_file == NULL) {
			RAND_file_name(filename, sizeof(filename));
			randfile = filename;
		} else if (*rand_file != '/') {
			snprintf(filename, sizeof(filename), "%s/%s",
			    keysdir, rand_file);
			randfile = filename;
		} else
			randfile = rand_file;

		if ((bytes = RAND_load_file(randfile, -1)) == 0) {
			msyslog(LOG_ERR,
			    "crypto_setup: random seed file %s missing",
			    randfile);
			exit (-1);
		}
		get_systime(&seed);
		RAND_seed(&seed, sizeof(l_fp));
		RAND_write_file(randfile);
		DPRINTF(1, ("crypto_setup: OpenSSL version %lx random seed file %s bytes read %d\n",
			    SSLeay(), randfile, bytes));
	}


	gethostname(hostname, sizeof(hostname));
	if (host_filename != NULL)
		strlcpy(hostname, host_filename, sizeof(hostname));
	if (passwd == NULL)
		passwd = estrdup(hostname);
	memset(&hostval, 0, sizeof(hostval));
	memset(&pubkey, 0, sizeof(pubkey));
	memset(&tai_leap, 0, sizeof(tai_leap));


	snprintf(filename, sizeof(filename), "ntpkey_host_%s", hostname);
	pinfo = crypto_key(filename, passwd, NULL);
	if (pinfo == NULL) {
		msyslog(LOG_ERR,
		    "crypto_setup: host key file %s not found or corrupt",
		    filename);
		exit (-1);
	}
	if (pinfo->pkey->type != EVP_PKEY_RSA) {
		msyslog(LOG_ERR,
		    "crypto_setup: host key is not RSA key type");
		exit (-1);
	}
	host_pkey = pinfo->pkey;
	sign_pkey = host_pkey;
	hostval.fstamp = htonl(pinfo->fstamp);


	len = i2d_PublicKey(host_pkey, NULL);
	ptr = emalloc(len);
	pubkey.ptr = ptr;
	i2d_PublicKey(host_pkey, &ptr);
	pubkey.fstamp = hostval.fstamp;
	pubkey.vallen = htonl(len);


	snprintf(filename, sizeof(filename), "ntpkey_sign_%s", hostname);
	pinfo = crypto_key(filename, passwd, NULL);
	if (pinfo != NULL)
		sign_pkey = pinfo->pkey;


	snprintf(filename, sizeof(filename), "ntpkey_cert_%s", hostname);
	cinfo = crypto_cert(filename);
	if (cinfo == NULL) {
		msyslog(LOG_ERR,
		    "crypto_setup: certificate file %s not found or corrupt",
		    filename);
		exit (-1);
	}
	cert_host = cinfo;
	sign_digest = cinfo->digest;
	sign_siglen = EVP_PKEY_size(sign_pkey);
	if (cinfo->flags & CERT_PRIV)
		crypto_flags |= CRYPTO_FLAG_PRIV;


	if (strcmp(cinfo->subject, cinfo->issuer) != 0) {
		msyslog(LOG_ERR,
		    "crypto_setup: certificate %s is not self-signed",
		    filename);
		exit (-1);
	}
	hostval.ptr = estrdup(cinfo->subject);
	hostval.vallen = htonl(strlen(cinfo->subject));
	sys_hostname = hostval.ptr;
	ptr = (u_char *)strchr(sys_hostname, '@');
	if (ptr != NULL)
		sys_groupname = estrdup((char *)++ptr);
	if (ident_filename != NULL)
		strlcpy(hostname, ident_filename, sizeof(hostname));


	snprintf(filename, sizeof(filename), "ntpkey_iffkey_%s",
	    hostname);
	iffkey_info = crypto_key(filename, passwd, NULL);
	if (iffkey_info != NULL)
		crypto_flags |= CRYPTO_FLAG_IFF;


	snprintf(filename, sizeof(filename), "ntpkey_gqkey_%s",
	    hostname);
	gqkey_info = crypto_key(filename, passwd, NULL);
	if (gqkey_info != NULL)
		crypto_flags |= CRYPTO_FLAG_GQ;


	snprintf(filename, sizeof(filename), "ntpkey_mvkey_%s",
	    hostname);
	mvkey_info = crypto_key(filename, passwd, NULL);
	if (mvkey_info != NULL)
		crypto_flags |= CRYPTO_FLAG_MV;


	crypto_flags |= CRYPTO_FLAG_ENAB | (cinfo->nid << 16);
	snprintf(statstr, sizeof(statstr), "setup 0x%x host %s %s",
	    crypto_flags, hostname, OBJ_nid2ln(cinfo->nid));
	record_crypto_stats(NULL, statstr);
	DPRINTF(1, ("crypto_setup: %s\n", statstr));
}
