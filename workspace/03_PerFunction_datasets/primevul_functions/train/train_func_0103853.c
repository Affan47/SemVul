cert_hike(
	struct peer *peer,
	struct cert_info *yp
	)
{
	struct cert_info *xp;
	X509	*cert;
	const u_char *ptr;


	if (peer->issuer != NULL)
		free(peer->issuer);
	peer->issuer = estrdup(yp->issuer);
	xp = peer->xinfo;
	peer->xinfo = yp;


	if (strcmp(yp->subject, yp->issuer) == 0) {
		if (!(yp->flags & CERT_TRUST))
			return (XEVNT_OK);


		peer->crypto |= CRYPTO_FLAG_CERT;
		peer->grpkey = yp->grpkey;
		if (peer->ident == NULL || !(peer->crypto &
		    CRYPTO_FLAG_MASK))
			peer->crypto |= CRYPTO_FLAG_VRFY;
	}


	if (xp == NULL)
		return (XEVNT_OK);

	ptr = (u_char *)xp->cert.ptr;
	cert = d2i_X509(NULL, &ptr, ntohl(xp->cert.vallen));
	if (cert == NULL) {
		xp->flags |= CERT_ERROR;
		return (XEVNT_CRT);
	}
	if (X509_verify(cert, yp->pkey) <= 0) {
		X509_free(cert);
		xp->flags |= CERT_ERROR;
		return (XEVNT_VFY);
	}
	X509_free(cert);


	if ((calcomp(&(xp->first), &(yp->first)) < 0)
	|| (calcomp(&(xp->first), &(yp->last)) > 0)) {
		xp->flags |= CERT_ERROR;
		return (XEVNT_PER);
	}
	xp->flags |= CERT_SIGN;
	return (XEVNT_OK);
}
