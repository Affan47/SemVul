cert_install(
	struct exten *ep,
	struct peer *peer
	)
{
	struct cert_info *cp, *xp, **zp;


	if ((cp = cert_parse((u_char *)ep->pkt, (long)ntohl(ep->vallen),
	    (tstamp_t)ntohl(ep->fstamp))) == NULL)
		return (NULL);


	zp = &cinfo;
	for (xp = cinfo; xp != NULL; xp = xp->link) {
		if (strcmp(cp->subject, xp->subject) == 0 &&
		    strcmp(cp->issuer, xp->issuer) == 0) {
			if (ntohl(cp->cert.fstamp) <=
			    ntohl(xp->cert.fstamp)) {
				cert_free(cp);
				cp = xp;
			} else {
				*zp = xp->link;
				cert_free(xp);
				xp = NULL;
			}
			break;
		}
		zp = &xp->link;
	}
	if (xp == NULL) {
		cp->link = cinfo;
		cinfo = cp;
	}
	cp->flags |= CERT_VALID;
	crypto_update();
	return (cp);
}
