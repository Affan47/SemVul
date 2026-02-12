PJ_DEF(pj_status_t) pj_stun_msg_encode(pj_stun_msg *msg,
				       pj_uint8_t *buf, pj_size_t buf_size,
				       unsigned options,
				       const pj_str_t *key,
				       pj_size_t *p_msg_len)
{
    pj_uint8_t *start = buf;
    pj_stun_msgint_attr *amsgint = NULL;
    pj_stun_fingerprint_attr *afingerprint = NULL;
    unsigned printed = 0, body_len;
    pj_status_t status;
    unsigned i;


    PJ_ASSERT_RETURN(msg && buf && buf_size, PJ_EINVAL);

    PJ_UNUSED_ARG(options);
    PJ_ASSERT_RETURN(options == 0, PJ_EINVAL);


    if (buf_size < sizeof(pj_stun_msg_hdr))
	return PJ_ETOOSMALL;

    PUTVAL16H(buf, 0, msg->hdr.type);
    PUTVAL16H(buf, 2, 0);
    PUTVAL32H(buf, 4, msg->hdr.magic);
    pj_memcpy(buf+8, msg->hdr.tsx_id, sizeof(msg->hdr.tsx_id));

    buf += sizeof(pj_stun_msg_hdr);
    buf_size -= sizeof(pj_stun_msg_hdr);


    for (i=0; i<msg->attr_count; ++i) {
	const struct attr_desc *adesc;
	const pj_stun_attr_hdr *attr_hdr = msg->attr[i];

	if (attr_hdr->type == PJ_STUN_ATTR_MESSAGE_INTEGRITY) {
	    pj_assert(amsgint == NULL);
	    amsgint = (pj_stun_msgint_attr*) attr_hdr;


	    break;

	} else if (attr_hdr->type == PJ_STUN_ATTR_FINGERPRINT) {
	    afingerprint = (pj_stun_fingerprint_attr*) attr_hdr;
	    break;
	}

	adesc = find_attr_desc(attr_hdr->type);
	if (adesc) {
	    status = adesc->encode_attr(attr_hdr, buf, (unsigned)buf_size,
					&msg->hdr, &printed);
	} else {

	    const pj_stun_binary_attr *bin_attr = (const pj_stun_binary_attr*)
						   attr_hdr;
	    PJ_ASSERT_RETURN(bin_attr->magic == PJ_STUN_MAGIC, PJ_EBUG);
	    status = encode_binary_attr(bin_attr, buf, (unsigned)buf_size,
					&msg->hdr, &printed);
	}

	if (status != PJ_SUCCESS)
	    return status;

	buf += printed;
	buf_size -= printed;
    }


    for ( ++i; i<msg->attr_count; ++i) {
	const pj_stun_attr_hdr *attr_hdr = msg->attr[i];


	PJ_ASSERT_RETURN(afingerprint == NULL, PJNATH_ESTUNFINGERPOS);

	if (attr_hdr->type == PJ_STUN_ATTR_MESSAGE_INTEGRITY) {

	    PJ_ASSERT_RETURN(amsgint == NULL,
			     PJNATH_ESTUNMSGINTPOS);
	    amsgint = (pj_stun_msgint_attr*) attr_hdr;

	} else if (attr_hdr->type == PJ_STUN_ATTR_FINGERPRINT) {
	    afingerprint = (pj_stun_fingerprint_attr*) attr_hdr;
	}
    }

#if PJ_STUN_OLD_STYLE_MI_FINGERPRINT


    if (amsgint && afingerprint) {
	body_len = (pj_uint16_t)((buf - start) - 20 + 24 + 8);
    } else if (amsgint) {
	body_len = (pj_uint16_t)((buf - start) - 20 + 24);
    } else if (afingerprint) {
	body_len = (pj_uint16_t)((buf - start) - 20 + 8);
    } else {
	body_len = (pj_uint16_t)((buf - start) - 20);
    }
#else


    if (amsgint) {
	body_len = (pj_uint16_t)((buf - start) - 20 + 24);
    } else {
	body_len = (pj_uint16_t)((buf - start) - 20);
    }
#endif


    PUTVAL16H(start, 2, (pj_uint16_t)body_len);


    if (amsgint != NULL) {
	pj_hmac_sha1_context ctx;


	PJ_ASSERT_RETURN(key, PJ_EINVALIDOP);


	if (msg->attr_count>1 && i < msg->attr_count-2) {

	    pj_assert(PJ_FALSE);
	    return PJNATH_ESTUNMSGINTPOS;

	} else if (i == msg->attr_count-2)  {
	    if (msg->attr[i+1]->type != PJ_STUN_ATTR_FINGERPRINT) {

		pj_assert(PJ_FALSE);
		return PJNATH_ESTUNMSGINTPOS;
	    } else {
		afingerprint = (pj_stun_fingerprint_attr*) msg->attr[i+1];
	    }
	}


	pj_hmac_sha1_init(&ctx, (const pj_uint8_t*)key->ptr,
			  (unsigned)key->slen);
	pj_hmac_sha1_update(&ctx, (const pj_uint8_t*)start,
			    (unsigned)(buf-start));
#if PJ_STUN_OLD_STYLE_MI_FINGERPRINT

	if ((buf-start) & 0x3F) {
	    pj_uint8_t zeroes[64];
	    pj_bzero(zeroes, sizeof(zeroes));
	    pj_hmac_sha1_update(&ctx, zeroes, 64-((buf-start) & 0x3F));
	}
#endif
	pj_hmac_sha1_final(&ctx, amsgint->hmac);


	status = encode_msgint_attr(amsgint, buf, (unsigned)buf_size,
			            &msg->hdr, &printed);
	if (status != PJ_SUCCESS)
	    return status;

	buf += printed;
	buf_size -= printed;
    }


    if (afingerprint != NULL) {

#if !PJ_STUN_OLD_STYLE_MI_FINGERPRINT

	PUTVAL16H(start, 2,
		 (pj_uint16_t)(GETVAL16H(start, 2)+8));
#endif

	afingerprint->value = pj_crc32_calc(start, buf-start);
	afingerprint->value ^= STUN_XOR_FINGERPRINT;


	status = encode_uint_attr(afingerprint, buf, (unsigned)buf_size,
				  &msg->hdr, &printed);
	if (status != PJ_SUCCESS)
	    return status;

	buf += printed;
	buf_size -= printed;
    }


    msg->hdr.length = (pj_uint16_t) ((buf - start) - 20);


    if (p_msg_len)
	*p_msg_len = (buf - start);

    return PJ_SUCCESS;
}
