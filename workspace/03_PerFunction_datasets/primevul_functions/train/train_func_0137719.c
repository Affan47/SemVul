crypto_recv(
	struct peer *peer,
	struct recvbuf *rbufp
	)
{
	const EVP_MD *dp;
	u_int32	*pkt;
	struct autokey *ap, *bp;
	struct exten *ep, *fp;
	struct cert_info *xinfo;
	int	has_mac;
	int	authlen;
	associd_t associd;
	tstamp_t fstamp = 0;
	u_int	len;
	u_int	code;
	u_int	vallen = 0;
	X509	*cert;
	char	statstr[NTP_MAXSTRLEN];
	keyid_t	cookie;
	int	hismode;
	int	rval = XEVNT_OK;
	const u_char *puch;
	u_int32 temp32;


	authlen = LEN_PKT_NOMAC;
	hismode = (int)PKT_MODE((&rbufp->recv_pkt)->li_vn_mode);
	while ((has_mac = rbufp->recv_length - authlen) > (int)MAX_MAC_LEN) {
		pkt = (u_int32 *)&rbufp->recv_pkt + authlen / 4;
		ep = (struct exten *)pkt;
		code = ntohl(ep->opcode) & 0xffff0000;
		len = ntohl(ep->opcode) & 0x0000ffff;

		associd = (associd_t)ntohl(pkt[1]);
		rval = XEVNT_OK;
		DPRINTF(1, ("crypto_recv: flags 0x%x ext offset %d len %u code 0x%x associd %d\n",
			    peer->crypto, authlen, len, code >> 16,
			    associd));


		if (((code >> 24) & 0x3f) != CRYPTO_VN || len < 8) {
			sys_badlength++;
			code |= CRYPTO_ERROR;
		}

		if (len >= VALUE_LEN) {
			fstamp = ntohl(ep->fstamp);
			vallen = ntohl(ep->vallen);


			if (   vallen == 0
			    || len - VALUE_LEN < vallen)
				return XEVNT_LEN;
		}
		switch (code) {


		case CRYPTO_ASSOC:


			if (peer->crypto & CRYPTO_FLAG_CERT) {
				rval = XEVNT_ERR;
				break;
			}
			if (peer->cmmd) {
				if (peer->assoc != associd) {
					rval = XEVNT_ERR;
					break;
				}
				free(peer->cmmd);
			}
			fp = emalloc(len);
			memcpy(fp, ep, len);
			fp->associd = htonl(peer->associd);
			peer->cmmd = fp;


		case CRYPTO_ASSOC | CRYPTO_RESP:


			if (peer->crypto) {
				if (peer->assoc != associd)
					rval = XEVNT_ERR;
				break;
			}
			INSIST(len >= VALUE_LEN);
			if (vallen == 0 || vallen > MAXHOSTNAME ||
			    len - VALUE_LEN < vallen) {
				rval = XEVNT_LEN;
				break;
			}
			DPRINTF(1, ("crypto_recv: ident host 0x%x %d server 0x%x %d\n",
				    crypto_flags, peer->associd, fstamp,
				    peer->assoc));
			temp32 = crypto_flags & CRYPTO_FLAG_MASK;


			if (crypto_flags & CRYPTO_FLAG_PRIV) {
				if (!(fstamp & CRYPTO_FLAG_PRIV)) {
					rval = XEVNT_KEY;
					break;
				}
				fstamp |= CRYPTO_FLAG_CERT |
				    CRYPTO_FLAG_VRFY | CRYPTO_FLAG_SIGN;


			} else if (hismode == MODE_ACTIVE || hismode ==
			    MODE_PASSIVE) {
				if ((temp32 && !(fstamp &
				    CRYPTO_FLAG_MASK)) ||
				    (!temp32 && (fstamp &
				    CRYPTO_FLAG_MASK))) {
					rval = XEVNT_KEY;
					break;
				}
			}


			temp32 = (fstamp >> 16) & 0xffff;
			dp =
			    (const EVP_MD *)EVP_get_digestbynid(temp32);
			if (dp == NULL) {
				rval = XEVNT_MD;
				break;
			}


			peer->assoc = associd;
			if (hismode == MODE_SERVER)
				fstamp |= CRYPTO_FLAG_AUTO;
			if (!(fstamp & CRYPTO_FLAG_TAI))
				fstamp |= CRYPTO_FLAG_LEAP;
			RAND_bytes((u_char *)&peer->hcookie, 4);
			peer->crypto = fstamp;
			peer->digest = dp;
			if (peer->subject != NULL)
				free(peer->subject);
			peer->subject = emalloc(vallen + 1);
			memcpy(peer->subject, ep->pkt, vallen);
			peer->subject[vallen] = '\0';
			if (peer->issuer != NULL)
				free(peer->issuer);
			peer->issuer = estrdup(peer->subject);
			snprintf(statstr, sizeof(statstr),
			    "assoc %d %d host %s %s", peer->associd,
			    peer->assoc, peer->subject,
			    OBJ_nid2ln(temp32));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_CERT | CRYPTO_RESP:


			if (len < VALUE_LEN)
				break;

			if ((rval = crypto_verify(ep, NULL, peer)) !=
			    XEVNT_OK)
				break;


			if ((xinfo = cert_install(ep, peer)) == NULL) {
				rval = XEVNT_CRT;
				break;
			}
			if ((rval = cert_hike(peer, xinfo)) != XEVNT_OK)
				break;


			if (peer->pkey == NULL) {
				puch = xinfo->cert.ptr;
				cert = d2i_X509(NULL, &puch,
				    ntohl(xinfo->cert.vallen));
				peer->pkey = X509_get_pubkey(cert);
				X509_free(cert);
			}
			peer->flash &= ~TEST8;
			temp32 = xinfo->nid;
			snprintf(statstr, sizeof(statstr),
			    "cert %s %s 0x%x %s (%u) fs %u",
			    xinfo->subject, xinfo->issuer, xinfo->flags,
			    OBJ_nid2ln(temp32), temp32,
			    ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_IFF | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, NULL, peer)) !=
			    XEVNT_OK)
				break;


			if ((rval = crypto_iff(ep, peer)) != XEVNT_OK)
				break;

			peer->crypto |= CRYPTO_FLAG_VRFY;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr), "iff %s fs %u",
			    peer->issuer, ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_GQ | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, NULL, peer)) !=
			    XEVNT_OK)
				break;


			if ((rval = crypto_gq(ep, peer)) != XEVNT_OK)
				break;

			peer->crypto |= CRYPTO_FLAG_VRFY;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr), "gq %s fs %u",
			    peer->issuer, ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_MV | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, NULL, peer)) !=
			    XEVNT_OK)
				break;


			if ((rval = crypto_mv(ep, peer)) != XEVNT_OK)
				break;

			peer->crypto |= CRYPTO_FLAG_VRFY;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr), "mv %s fs %u",
			    peer->issuer, ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_COOK | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, &peer->cookval,
			    peer)) != XEVNT_OK)
				break;


			if (vallen == (u_int)EVP_PKEY_size(host_pkey)) {
				u_int32 *cookiebuf = malloc(
				    RSA_size(host_pkey->pkey.rsa));
				if (!cookiebuf) {
					rval = XEVNT_CKY;
					break;
				}

				if (RSA_private_decrypt(vallen,
				    (u_char *)ep->pkt,
				    (u_char *)cookiebuf,
				    host_pkey->pkey.rsa,
				    RSA_PKCS1_OAEP_PADDING) != 4) {
					rval = XEVNT_CKY;
					free(cookiebuf);
					break;
				} else {
					cookie = ntohl(*cookiebuf);
					free(cookiebuf);
				}
			} else {
				rval = XEVNT_CKY;
				break;
			}


			key_expire(peer);
			if (hismode == MODE_ACTIVE || hismode ==
			    MODE_PASSIVE)
				peer->pcookie = peer->hcookie ^ cookie;
			else
				peer->pcookie = cookie;
			peer->crypto |= CRYPTO_FLAG_COOK;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr),
			    "cook %x ts %u fs %u", peer->pcookie,
			    ntohl(ep->tstamp), ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_AUTO | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, &peer->recval,
			    peer)) != XEVNT_OK)
				break;


			if ((peer->cast_flags & MDF_BCLNT) &&
			    peer->assoc != associd)
				break;


			if (ep->tstamp == 0)
				break;

			if (peer->recval.ptr == NULL)
				peer->recval.ptr =
				    emalloc(sizeof(struct autokey));
			bp = (struct autokey *)peer->recval.ptr;
			peer->recval.tstamp = ep->tstamp;
			peer->recval.fstamp = ep->fstamp;
			ap = (struct autokey *)ep->pkt;
			bp->seq = ntohl(ap->seq);
			bp->key = ntohl(ap->key);
			peer->pkeyid = bp->key;
			peer->crypto |= CRYPTO_FLAG_AUTO;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr),
			    "auto seq %d key %x ts %u fs %u", bp->seq,
			    bp->key, ntohl(ep->tstamp),
			    ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_SIGN | CRYPTO_RESP:


			if ((rval = crypto_verify(ep, NULL, peer)) !=
			    XEVNT_OK)
				break;


			if ((xinfo = cert_install(ep, peer)) == NULL) {
				rval = XEVNT_CRT;
				break;
			}
			peer->crypto |= CRYPTO_FLAG_SIGN;
			peer->flash &= ~TEST8;
			temp32 = xinfo->nid;
			snprintf(statstr, sizeof(statstr),
			    "sign %s %s 0x%x %s (%u) fs %u",
			    xinfo->subject, xinfo->issuer, xinfo->flags,
			    OBJ_nid2ln(temp32), temp32,
			    ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_LEAP | CRYPTO_RESP:


			rval = crypto_verify(ep, NULL, peer);
			if ((rval   != XEVNT_OK          ) ||
			    (vallen != 3*sizeof(uint32_t))  )
				break;


			if (sys_leap != LEAP_NOTINSYNC)
				leapsec_autokey_tai(ntohl(ep->pkt[0]),
						    rbufp->recv_time.l_ui, NULL);
			tai_leap.tstamp = ep->tstamp;
			tai_leap.fstamp = ep->fstamp;
			crypto_update();
			mprintf_event(EVNT_TAI, peer,
				      "%d seconds", ntohl(ep->pkt[0]));
			peer->crypto |= CRYPTO_FLAG_LEAP;
			peer->flash &= ~TEST8;
			snprintf(statstr, sizeof(statstr),
				 "leap TAI offset %d at %u expire %u fs %u",
				 ntohl(ep->pkt[0]), ntohl(ep->pkt[1]),
				 ntohl(ep->pkt[2]), ntohl(ep->fstamp));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			break;


		case CRYPTO_CERT:
		case CRYPTO_IFF:
		case CRYPTO_GQ:
		case CRYPTO_MV:
		case CRYPTO_COOK:
		case CRYPTO_SIGN:
			if (len < VALUE_LEN) {
				rval = XEVNT_LEN;
				break;
			}


		default:
			if (code & (CRYPTO_RESP | CRYPTO_ERROR)) {
				rval = XEVNT_ERR;
			} else if (peer->cmmd == NULL) {
				fp = emalloc(len);
				memcpy(fp, ep, len);
				peer->cmmd = fp;
			}
		}


		if (rval != XEVNT_OK) {
			snprintf(statstr, sizeof(statstr),
			    "%04x %d %02x %s", htonl(ep->opcode),
			    associd, rval, eventstr(rval));
			record_crypto_stats(&peer->srcadr, statstr);
			DPRINTF(1, ("crypto_recv: %s\n", statstr));
			return (rval);
		}
		authlen += (len + 3) / 4 * 4;
	}
	return (rval);
}
