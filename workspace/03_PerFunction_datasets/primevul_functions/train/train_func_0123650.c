mobility_print(const u_char *bp, const u_char *bp2 _U_)
{
	const struct ip6_mobility *mh;
	const u_char *ep;
	unsigned mhlen, hlen;
	u_int8_t type;

	mh = (struct ip6_mobility *)bp;


	ep = snapend;

	if (!TTEST(mh->ip6m_len)) {


		mhlen = ep - bp;
		goto trunc;
	}
	mhlen = (mh->ip6m_len + 1) << 3;


	TCHECK(mh->ip6m_type);
	type = mh->ip6m_type;
	switch (type) {
	case IP6M_BINDING_REQUEST:
		printf("mobility: BRR");
		hlen = IP6M_MINLEN;
		break;
	case IP6M_HOME_TEST_INIT:
	case IP6M_CAREOF_TEST_INIT:
		printf("mobility: %soTI",
			type == IP6M_HOME_TEST_INIT ? "H" : "C");
		hlen = IP6M_MINLEN;
    		if (vflag) {
			TCHECK2(*mh, hlen + 8);
			printf(" %s Init Cookie=%08x:%08x",
			       type == IP6M_HOME_TEST_INIT ? "Home" : "Care-of",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		}
		hlen += 8;
		break;
	case IP6M_HOME_TEST:
	case IP6M_CAREOF_TEST:
		printf("mobility: %soT",
			type == IP6M_HOME_TEST ? "H" : "C");
		TCHECK(mh->ip6m_data16[0]);
		printf(" nonce id=0x%x", EXTRACT_16BITS(&mh->ip6m_data16[0]));
		hlen = IP6M_MINLEN;
    		if (vflag) {
			TCHECK2(*mh, hlen + 8);
			printf(" %s Init Cookie=%08x:%08x",
			       type == IP6M_HOME_TEST ? "Home" : "Care-of",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		}
		hlen += 8;
    		if (vflag) {
			TCHECK2(*mh, hlen + 8);
			printf(" %s Keygen Token=%08x:%08x",
			       type == IP6M_HOME_TEST ? "Home" : "Care-of",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		}
		hlen += 8;
		break;
	case IP6M_BINDING_UPDATE:
		printf("mobility: BU");
		TCHECK(mh->ip6m_data16[0]);
		printf(" seq#=%u", EXTRACT_16BITS(&mh->ip6m_data16[0]));
		hlen = IP6M_MINLEN;
		TCHECK2(*mh, hlen + 1);
		if (bp[hlen] & 0xf0)
			printf(" ");
		if (bp[hlen] & 0x80)
			printf("A");
		if (bp[hlen] & 0x40)
			printf("H");
		if (bp[hlen] & 0x20)
			printf("L");
		if (bp[hlen] & 0x10)
			printf("K");

		hlen += 1;

		hlen += 1;
		TCHECK2(*mh, hlen + 2);

		printf(" lifetime=%u", EXTRACT_16BITS(&bp[hlen]) << 2);
		hlen += 2;
		break;
	case IP6M_BINDING_ACK:
		printf("mobility: BA");
		TCHECK(mh->ip6m_data8[0]);
		printf(" status=%u", mh->ip6m_data8[0]);
		if (mh->ip6m_data8[1] & 0x80)
			printf(" K");

		hlen = IP6M_MINLEN;
		TCHECK2(*mh, hlen + 2);
		printf(" seq#=%u", EXTRACT_16BITS(&bp[hlen]));
		hlen += 2;
		TCHECK2(*mh, hlen + 2);

		printf(" lifetime=%u", EXTRACT_16BITS(&bp[hlen]) << 2);
		hlen += 2;
		break;
	case IP6M_BINDING_ERROR:
		printf("mobility: BE");
		TCHECK(mh->ip6m_data8[0]);
		printf(" status=%u", mh->ip6m_data8[0]);

		hlen = IP6M_MINLEN;
		TCHECK2(*mh, hlen + 16);
		printf(" homeaddr %s", ip6addr_string(&bp[hlen]));
		hlen += 16;
		break;
	default:
		printf("mobility: type-#%u len=%u", type, mh->ip6m_len);
		return(mhlen);
		break;
	}
    	if (vflag)
		mobility_opt_print(&bp[hlen], mhlen - hlen);

	return(mhlen);

 trunc:
	fputs("[|MOBILITY]", stdout);
	return(mhlen);
}
