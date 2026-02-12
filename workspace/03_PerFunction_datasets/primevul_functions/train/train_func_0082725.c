serialNumberAndIssuerSerialCheck(
	struct berval *in,
	struct berval *sn,
	struct berval *is,
	struct berval *i_sn,
	void *ctx )
{

	enum {
		HAVE_NONE = 0x0,
		HAVE_SN = 0x1,
		HAVE_ISSUER = 0x2,
		HAVE_ALL = ( HAVE_SN | HAVE_ISSUER )
	} have = HAVE_NONE, have2 = HAVE_NONE;
	int numdquotes = 0;
	struct berval x = *in;
	struct berval ni;

	if ( in->bv_len < 3 ) return LDAP_INVALID_SYNTAX;


	if ( in->bv_val[0] != '{' && in->bv_val[in->bv_len-1] != '}' ) return LDAP_INVALID_SYNTAX;

	x.bv_val++;
	x.bv_len -= 2;

	do {


		for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
			;
		}


		if ( strncasecmp( x.bv_val, "issuer", STRLENOF("issuer") ) == 0 ) {
			if ( have & HAVE_ISSUER ) {
				return LDAP_INVALID_SYNTAX;
			}


			x.bv_val += STRLENOF("issuer");
			x.bv_len -= STRLENOF("issuer");

			if ( x.bv_val[0] != ' ' ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;


			for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
				;
			}

			if ( x.bv_val[0] != '{'  ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;


			for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
				;
			}

			if ( strncasecmp( x.bv_val, "baseCertificateID ", STRLENOF("baseCertificateID ") ) != 0 ) {
				return LDAP_INVALID_SYNTAX;
			}
			x.bv_val += STRLENOF("baseCertificateID ");
			x.bv_len -= STRLENOF("baseCertificateID ");


			for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
				;
			}

			if ( x.bv_val[0] != '{'  ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;

			do {

				for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
					;
				}


				if ( strncasecmp( x.bv_val, "issuer ", STRLENOF("issuer ") ) == 0 ) {
					if ( have2 & HAVE_ISSUER ) {
						return LDAP_INVALID_SYNTAX;
					}

					x.bv_val += STRLENOF("issuer ");
					x.bv_len -= STRLENOF("issuer ");


					for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
						;
					}

					if ( x.bv_val[0] != '{'  ) return LDAP_INVALID_SYNTAX;
					x.bv_val++;
					x.bv_len--;


					for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
						;
					}

					if ( strncasecmp( x.bv_val, "directoryName:rdnSequence:", STRLENOF("directoryName:rdnSequence:") ) != 0 ) {
						return LDAP_INVALID_SYNTAX;
					}
					x.bv_val += STRLENOF("directoryName:rdnSequence:");
					x.bv_len -= STRLENOF("directoryName:rdnSequence:");

					if ( x.bv_val[0] != '"' ) return LDAP_INVALID_SYNTAX;
					x.bv_val++;
					x.bv_len--;

					is->bv_val = x.bv_val;
					is->bv_len = 0;

					for ( ; is->bv_len < x.bv_len; ) {
						if ( is->bv_val[is->bv_len] != '"' ) {
							is->bv_len++;
							continue;
						}
						if ( is->bv_val[is->bv_len + 1] == '"' ) {

							numdquotes++;
							is->bv_len += 2;
							continue;
						}
						break;
					}
					x.bv_val += is->bv_len + 1;
					x.bv_len -= is->bv_len + 1;


					for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
						;
					}

					if ( x.bv_val[0] !=  '}' ) return LDAP_INVALID_SYNTAX;
					x.bv_val++;
					x.bv_len--;

					have2 |= HAVE_ISSUER;

				} else if ( strncasecmp( x.bv_val, "serial ", STRLENOF("serial ") ) == 0 ) {
					if ( have2 & HAVE_SN ) {
						return LDAP_INVALID_SYNTAX;
					}

					x.bv_val += STRLENOF("serial ");
					x.bv_len -= STRLENOF("serial ");


					for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len--) {
						;
					}

					if ( checkNum( &x, i_sn ) ) {
						return LDAP_INVALID_SYNTAX;
					}

					x.bv_val += i_sn->bv_len;
					x.bv_len -= i_sn->bv_len;

					have2 |= HAVE_SN;

				} else {
					return LDAP_INVALID_SYNTAX;
				}


				for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
					;
				}

				if ( have2 == HAVE_ALL ) {
					break;
				}

				if ( x.bv_val[0] != ',' ) return LDAP_INVALID_SYNTAX;
				x.bv_val++;
				x.bv_len--;
			} while ( 1 );

			if ( x.bv_val[0] !=  '}' ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;


			for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
				;
			}

			if ( x.bv_val[0] !=  '}' ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;

			have |= HAVE_ISSUER;

		} else if ( strncasecmp( x.bv_val, "serialNumber", STRLENOF("serialNumber") ) == 0 ) {
			if ( have & HAVE_SN ) {
				return LDAP_INVALID_SYNTAX;
			}


			x.bv_val += STRLENOF("serialNumber");
			x.bv_len -= STRLENOF("serialNumber");

			if ( x.bv_val[0] != ' ' ) return LDAP_INVALID_SYNTAX;
			x.bv_val++;
			x.bv_len--;


			for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
				;
			}

			if ( checkNum( &x, sn ) ) {
				return LDAP_INVALID_SYNTAX;
			}

			x.bv_val += sn->bv_len;
			x.bv_len -= sn->bv_len;

			have |= HAVE_SN;

		} else {
			return LDAP_INVALID_SYNTAX;
		}


		for ( ; (x.bv_val[0] == ' ') && x.bv_len; x.bv_val++, x.bv_len-- ) {
			;
		}

		if ( have == HAVE_ALL ) {
			break;
		}

		if ( x.bv_val[0] != ',' ) {
			return LDAP_INVALID_SYNTAX;
		}
		x.bv_val++ ;
		x.bv_len--;
	} while ( 1 );


	if( x.bv_len ) return LDAP_INVALID_SYNTAX;

	if ( numdquotes == 0 ) {
		ber_dupbv_x( &ni, is, ctx );

	} else {
		ber_len_t src, dst;

		ni.bv_len = is->bv_len - numdquotes;
		ni.bv_val = ber_memalloc_x( ni.bv_len + 1, ctx );
		for ( src = 0, dst = 0; src < is->bv_len; src++, dst++ ) {
			if ( is->bv_val[src] == '"' ) {
				src++;
			}
			ni.bv_val[dst] = is->bv_val[src];
		}
		ni.bv_val[dst] = '\0';
	}

	*is = ni;


	return 0;
}
