relpTcpGetCN(relpTcp_t *pThis, gnutls_x509_crt_t cert, char *namebuf, int lenNamebuf)
{
	int r;
	int gnuRet;
	int i,j;
	int bFound;
	size_t size;
	char szDN[1024];

	size = sizeof(szDN);
	gnuRet = gnutls_x509_crt_get_dn(cert, (char*)szDN, &size);
	if(chkGnutlsCode(pThis, "Failed to obtain DN from certificate", RELP_RET_ERR_TLS, gnuRet)) {
		r = 1; goto done;
	}


	i = 0;
	bFound = 0;
	while(!bFound && szDN[i] != '\0') {


		if(szDN[i] == 'C' && szDN[i+1] == 'N' && szDN[i+2] == '=') {
			bFound = 1;
			i += 2;
		}
		i++;

	}

	if(!bFound) {
		r = 1; goto done;
	}


	j = 0;
	while(szDN[i] != '\0' && szDN[i] != ',' && j < lenNamebuf-1) {
		if(szDN[i] == '\\') {

			r = 2; goto done;
		} else {
			namebuf[j++] = szDN[i];
		}
		++i;
	}
	namebuf[j] = '\0';


	r = 0;

done:
	return r;
}
