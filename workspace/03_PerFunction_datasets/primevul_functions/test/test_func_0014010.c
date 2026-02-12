integerVal2Key(
	struct berval *in,
	struct berval *key,
	struct berval *tmp,
	void *ctx )
{


	ber_slen_t k = index_intlen_strlen;
	ber_len_t chop = 0;
	unsigned signmask = ~0x7fU;
	unsigned char lenbuf[sizeof(k) + 2], *lenp, neg = 0xff;
	struct berval val = *in, itmp = *tmp;

	if ( val.bv_val[0] != '-' ) {
		neg = 0;
		--k;
	}


	if ( val.bv_len > (ber_len_t) k ) {
		chop = (val.bv_len-k+2)/INDEX_INTLEN_CHOP;
		val.bv_len -= chop * INDEX_INTLEN_CHOP;
		chop *= INDEX_INTLEN_CHOPBYTES;
	}

	if ( lutil_str2bin( &val, &itmp, ctx )) {
		return LDAP_INVALID_SYNTAX;
	}


	if ( itmp.bv_val[0] == neg ) {
		itmp.bv_val++;
		itmp.bv_len--;
	}

	k = (ber_slen_t) index_intlen - (ber_slen_t) (itmp.bv_len + chop);
	if ( k > 0 ) {
		assert( chop == 0 );
		memset( key->bv_val, neg, k );
	} else if ( k != 0 || ((itmp.bv_val[0] ^ neg) & 0xc0) ) {

		lenp = lenbuf + sizeof(lenbuf);
		chop = - (ber_len_t) k;
		do {
			*--lenp = ((unsigned char) chop & 0xff) ^ neg;
			signmask >>= 1;
		} while ( (chop >>= 8) != 0 || (signmask >> 1) & (*lenp ^ neg) );


		k = (lenbuf + sizeof(lenbuf)) - lenp;
		if ( k > (ber_slen_t) index_intlen )
			k = index_intlen;
		memcpy( key->bv_val, lenp, k );
		itmp.bv_len = index_intlen - k;
	}
	memcpy( key->bv_val + k, itmp.bv_val, itmp.bv_len );
	key->bv_val[0] ^= (unsigned char) signmask & 0xff;
	return 0;
}
