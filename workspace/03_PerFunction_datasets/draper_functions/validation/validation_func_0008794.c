gre_print_1(const u_char *bp, u_int length)
{
	u_int len = length;
	u_int16_t flags, prot;

	flags = EXTRACT_16BITS(bp);
	len -= 2;
	bp += 2;

	if (vflag)
            printf(", Flags [%s]",
                   bittok2str(gre_flag_values,"none",flags));

	if (len < 2)
		goto trunc;
	prot = EXTRACT_16BITS(bp);
	len -= 2;
	bp += 2;


	if (flags & GRE_KP) {
		u_int32_t k;

		if (len < 4)
			goto trunc;
		k = EXTRACT_32BITS(bp);
		printf(", call %d", k & 0xffff);
		len -= 4;
		bp += 4;
	}

	if (flags & GRE_SP) {
		if (len < 4)
			goto trunc;
		printf(", seq %u", EXTRACT_32BITS(bp));
		bp += 4;
		len -= 4;
	}

	if (flags & GRE_AP) {
		if (len < 4)
			goto trunc;
		printf(", ack %u", EXTRACT_32BITS(bp));
		bp += 4;
		len -= 4;
	}

	if ((flags & GRE_SP) == 0)
		printf(", no-payload");

        if (eflag)
            printf(", proto %s (0x%04x)",
                   tok2str(ethertype_values,"unknown",prot),
                   prot);

        printf(", length %u",length);

        if ((flags & GRE_SP) == 0)
            return;

        if (vflag < 1)
            printf(": ");
        else
            printf("\n\t");

	switch (prot) {
	case ETHERTYPE_PPP:
                ppp_print(bp, len);
		break;
	default:
		printf("gre-proto-0x%x", prot);
		break;
	}
	return;

trunc:
	printf("[|gre]");
}
