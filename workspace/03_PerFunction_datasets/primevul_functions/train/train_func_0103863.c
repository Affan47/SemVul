crypto_xmit(
	struct peer *peer,
	struct pkt *xpkt,
	struct recvbuf *rbufp,
	int	start,
	struct exten *ep,
	keyid_t cookie
	)
{
	struct exten *fp;
	struct cert_info *cp, *xp, *yp;
	sockaddr_u *srcadr_sin;
	u_int32	*pkt;
	u_int	opcode;
	char	certname[MAXHOSTNAME + 1];
	char	statstr[NTP_MAXSTRLEN];
	tstamp_t tstamp;
	struct calendar tscal;
	u_int	vallen;
	struct value vtemp;
	associd_t associd;
	int	rval;
	int	len;
	keyid_t tcookie;


	pkt = (u_int32 *)xpkt + start / 4;
	fp = (struct exten *)pkt;
	opcode = ntohl(ep->opcode);
	if (peer != NULL) {
		srcadr_sin = &peer->srcadr;
		if (!(opcode & CRYPTO_RESP))
			peer->opcode = ep->opcode;
	} else {
		srcadr_sin = &rbufp->recv_srcadr;
	}
	associd = (associd_t) ntohl(ep->associd);
	len = 8;
	fp->opcode = htonl((opcode & 0xffff0000) | len);
	fp->associd = ep->associd;
	rval = XEVNT_OK;
	tstamp = crypto_time();
	switch (opcode & 0xffff0000) {


	case CRYPTO_ASSOC:
	case CRYPTO_ASSOC | CRYPTO_RESP:
		len = crypto_send(fp, &hostval, start);
		fp->fstamp = htonl(crypto_flags);
		break;


	case CRYPTO_CERT:
		memset(&vtemp, 0, sizeof(vtemp));
		vtemp.tstamp = ep->tstamp;
		vtemp.fstamp = ep->fstamp;
		vtemp.vallen = ep->vallen;
		vtemp.ptr = (u_char *)ep->pkt;
		len = crypto_send(fp, &vtemp, start);
		break;


	case CRYPTO_SIGN:
		(void)ntpcal_ntp_to_date(&tscal, tstamp, NULL);
		if ((calcomp(&tscal, &(cert_host->first)) < 0)
		|| (calcomp(&tscal, &(cert_host->last)) > 0))
			rval = XEVNT_PER;
		else
			len = crypto_send(fp, &cert_host->cert, start);
		break;


	case CRYPTO_CERT | CRYPTO_RESP:
		vallen = exten_payload_size(ep);
		if (vallen == 0 || vallen >= sizeof(certname) ) {
			rval = XEVNT_LEN;
			break;
		}


		memcpy(certname, ep->pkt, vallen);
		certname[vallen] = '\0';
		xp = yp = NULL;
		for (cp = cinfo; cp != NULL; cp = cp->link) {
			if (cp->flags & (CERT_PRIV | CERT_ERROR))
				continue;

			if (strcmp(certname, cp->subject) != 0)
				continue;

			if (strcmp(certname, cp->issuer) != 0)
				yp = cp;
			else if (cp ->flags & CERT_TRUST)
				xp = cp;
			continue;
		}


		if (xp == NULL)
			xp = yp;
		if (xp == NULL)
			break;

		if (tstamp == 0)
			break;

		len = crypto_send(fp, &xp->cert, start);
		break;


	case CRYPTO_IFF:
		if (peer == NULL)
			break;

		if ((rval = crypto_alice(peer, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_IFF | CRYPTO_RESP:
		if ((rval = crypto_bob(ep, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_GQ:
		if (peer == NULL)
			break;

		if ((rval = crypto_alice2(peer, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_GQ | CRYPTO_RESP:
		if ((rval = crypto_bob2(ep, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_MV:
		if (peer == NULL)
			break;

		if ((rval = crypto_alice3(peer, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_MV | CRYPTO_RESP:
		if ((rval = crypto_bob3(ep, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_SIGN | CRYPTO_RESP:
		if ((rval = cert_sign(ep, &vtemp)) == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_COOK:
		len = crypto_send(fp, &pubkey, start);
		break;


	case CRYPTO_COOK | CRYPTO_RESP:
		vallen = ntohl(ep->vallen);
		if (   vallen == 0
		    || (vallen >= MAX_VALLEN)
		    || (opcode & 0x0000ffff)  < VALUE_LEN + vallen) {
			rval = XEVNT_LEN;
			break;
		}
		if (peer == NULL)
			tcookie = cookie;
		else
			tcookie = peer->hcookie;
		if ((rval = crypto_encrypt((const u_char *)ep->pkt, vallen, &tcookie, &vtemp))
		    == XEVNT_OK) {
			len = crypto_send(fp, &vtemp, start);
			value_free(&vtemp);
		}
		break;


	case CRYPTO_AUTO | CRYPTO_RESP:
		if (peer == NULL) {
			if ((peer = findpeerbyassoc(associd)) == NULL) {
				rval = XEVNT_ERR;
				break;
			}
		}
		peer->flags &= ~FLAG_ASSOC;
		len = crypto_send(fp, &peer->sndval, start);
		break;


	case CRYPTO_LEAP | CRYPTO_RESP:
		len = crypto_send(fp, &tai_leap, start);
		break;


	default:
		if (opcode & CRYPTO_RESP)
			rval = XEVNT_ERR;
	}


	if (rval != XEVNT_OK) {
		u_int32	uint32;

		uint32 = CRYPTO_ERROR;
		opcode |= uint32;
		fp->opcode |= htonl(uint32);
		snprintf(statstr, sizeof(statstr),
		    "%04x %d %02x %s", opcode, associd, rval,
		    eventstr(rval));
		record_crypto_stats(srcadr_sin, statstr);
		DPRINTF(1, ("crypto_xmit: %s\n", statstr));
		if (!(opcode & CRYPTO_RESP))
			return (0);
	}
	DPRINTF(1, ("crypto_xmit: flags 0x%x offset %d len %d code 0x%x associd %d\n",
		    crypto_flags, start, len, opcode >> 16, associd));
	return (len);
}
