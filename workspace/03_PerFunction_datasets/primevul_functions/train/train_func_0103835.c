make_keylist(
	struct peer *peer,
	struct interface *dstadr
	)
{
	EVP_MD_CTX ctx;
	tstamp_t tstamp;
	struct autokey *ap;
	struct value *vp;
	keyid_t	keyid = 0;
	keyid_t	cookie;
	long	lifetime;
	u_int	len, mpoll;
	int	i;

	if (!dstadr)
		return XEVNT_ERR;


	tstamp = crypto_time();
	if (peer->keylist == NULL)
		peer->keylist = eallocarray(NTP_MAXSESSION,
					    sizeof(keyid_t));


	while (1) {
		keyid = ntp_random() & 0xffffffff;
		if (keyid <= NTP_MAXKEY)
			continue;

		if (authhavekey(keyid))
			continue;
		break;
	}


	mpoll = 1 << min(peer->ppoll, peer->hpoll);
	lifetime = min(1U << sys_automax, NTP_MAXSESSION * mpoll);
	if (peer->hmode == MODE_BROADCAST)
		cookie = 0;
	else
		cookie = peer->pcookie;
	for (i = 0; i < NTP_MAXSESSION; i++) {
		peer->keylist[i] = keyid;
		peer->keynumber = i;
		keyid = session_key(&dstadr->sin, &peer->srcadr, keyid,
		    cookie, lifetime + mpoll);
		lifetime -= mpoll;
		if (auth_havekey(keyid) || keyid <= NTP_MAXKEY ||
		    lifetime < 0 || tstamp == 0)
			break;
	}


	vp = &peer->sndval;
	if (vp->ptr == NULL)
		vp->ptr = emalloc(sizeof(struct autokey));
	ap = (struct autokey *)vp->ptr;
	ap->seq = htonl(peer->keynumber);
	ap->key = htonl(keyid);
	vp->tstamp = htonl(tstamp);
	vp->fstamp = hostval.tstamp;
	vp->vallen = htonl(sizeof(struct autokey));
	vp->siglen = 0;
	if (tstamp != 0) {
		if (vp->sig == NULL)
			vp->sig = emalloc(sign_siglen);
		EVP_SignInit(&ctx, sign_digest);
		EVP_SignUpdate(&ctx, (u_char *)vp, 12);
		EVP_SignUpdate(&ctx, vp->ptr, sizeof(struct autokey));
		if (EVP_SignFinal(&ctx, vp->sig, &len, sign_pkey)) {
			INSIST(len <= sign_siglen);
			vp->siglen = htonl(len);
			peer->flags |= FLAG_ASSOC;
		}
	}
	DPRINTF(1, ("make_keys: %d %08x %08x ts %u fs %u poll %d\n",
		    peer->keynumber, keyid, cookie, ntohl(vp->tstamp),
		    ntohl(vp->fstamp), peer->hpoll));
	return (XEVNT_OK);
}
