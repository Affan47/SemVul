int compute_password_element (pwd_session_t *session, uint16_t grp_num,
			      char const *password, int password_len,
			      char const *id_server, int id_server_len,
			      char const *id_peer, int id_peer_len,
			      uint32_t *token)
{
	BIGNUM *x_candidate = NULL, *rnd = NULL, *cofactor = NULL;
	HMAC_CTX *ctx = NULL;
	uint8_t pwe_digest[SHA256_DIGEST_LENGTH], *prfbuf = NULL, ctr;
	int nid, is_odd, primebitlen, primebytelen, ret = 0;

	ctx = HMAC_CTX_new();
	if (ctx == NULL) {
		DEBUG("failed allocating HMAC context");
		goto fail;
	}

	switch (grp_num) {
	case 19:
		nid = NID_X9_62_prime256v1;
		break;

	case 20:
		nid = NID_secp384r1;
		break;

	case 21:
		nid = NID_secp521r1;
		break;

	case 25:
		nid = NID_X9_62_prime192v1;
		break;

	case 26:
		nid = NID_secp224r1;
		break;

	default:
		DEBUG("unknown group %d", grp_num);
		goto fail;
	}

	session->pwe = NULL;
	session->order = NULL;
	session->prime = NULL;

	if ((session->group = EC_GROUP_new_by_curve_name(nid)) == NULL) {
		DEBUG("unable to create EC_GROUP");
		goto fail;
	}

	if (((rnd = BN_new()) == NULL) ||
	    ((cofactor = BN_new()) == NULL) ||
	    ((session->pwe = EC_POINT_new(session->group)) == NULL) ||
	    ((session->order = BN_new()) == NULL) ||
	    ((session->prime = BN_new()) == NULL) ||
	    ((x_candidate = BN_new()) == NULL)) {
		DEBUG("unable to create bignums");
		goto fail;
	}

	if (!EC_GROUP_get_curve_GFp(session->group, session->prime, NULL, NULL, NULL)) {
		DEBUG("unable to get prime for GFp curve");
		goto fail;
	}

	if (!EC_GROUP_get_order(session->group, session->order, NULL)) {
		DEBUG("unable to get order for curve");
		goto fail;
	}

	if (!EC_GROUP_get_cofactor(session->group, cofactor, NULL)) {
		DEBUG("unable to get cofactor for curve");
		goto fail;
	}

	primebitlen = BN_num_bits(session->prime);
	primebytelen = BN_num_bytes(session->prime);
	if ((prfbuf = talloc_zero_array(session, uint8_t, primebytelen)) == NULL) {
		DEBUG("unable to alloc space for prf buffer");
		goto fail;
	}
	ctr = 0;
	while (1) {
		if (ctr > 10) {
			DEBUG("unable to find random point on curve for group %d, something's fishy", grp_num);
			goto fail;
		}
		ctr++;


		H_Init(ctx);
		H_Update(ctx, (uint8_t *)token, sizeof(*token));
		H_Update(ctx, (uint8_t const *)id_peer, id_peer_len);
		H_Update(ctx, (uint8_t const *)id_server, id_server_len);
		H_Update(ctx, (uint8_t const *)password, password_len);
		H_Update(ctx, (uint8_t *)&ctr, sizeof(ctr));
		H_Final(ctx, pwe_digest);

		BN_bin2bn(pwe_digest, SHA256_DIGEST_LENGTH, rnd);
		if (eap_pwd_kdf(pwe_digest, SHA256_DIGEST_LENGTH, "EAP-pwd Hunting And Pecking",
			        strlen("EAP-pwd Hunting And Pecking"), prfbuf, primebitlen) != 0) {
			DEBUG("key derivation function failed");
			goto fail;
		}

		BN_bin2bn(prfbuf, primebytelen, x_candidate);


		if (primebitlen % 8) BN_rshift(x_candidate, x_candidate, (8 - (primebitlen % 8)));
		if (BN_ucmp(x_candidate, session->prime) >= 0) continue;


		is_odd = BN_is_odd(rnd) ? 1 : 0;


		if (!EC_POINT_set_compressed_coordinates_GFp(session->group, session->pwe, x_candidate, is_odd, NULL)) {
			continue;
		}


		if (!EC_POINT_is_on_curve(session->group, session->pwe, NULL)) {
			DEBUG("EAP-pwd: point is not on curve");
			continue;
		}

		if (BN_cmp(cofactor, BN_value_one())) {

			if (!EC_POINT_mul(session->group, session->pwe, NULL, session->pwe,
				cofactor, NULL)) {
				DEBUG("EAP-pwd: cannot multiply generator by order");
				continue;
			}

			if (EC_POINT_is_at_infinity(session->group, session->pwe)) {
				DEBUG("EAP-pwd: point is at infinity");
				continue;
			}
		}

		break;
	}

	session->group_num = grp_num;
	if (0) {
		fail:
		ret = -1;
	}


	BN_clear_free(cofactor);
	BN_clear_free(x_candidate);
	BN_clear_free(rnd);
	talloc_free(prfbuf);
	HMAC_CTX_free(ctx);

	return ret;
}
