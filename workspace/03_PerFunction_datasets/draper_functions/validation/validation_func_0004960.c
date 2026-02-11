bgp_route_refresh_print(const u_char *pptr, int len) {

        const struct bgp_route_refresh *bgp_route_refresh_header;
	char tokbuf[TOKBUFSIZE];
	char tokbuf2[TOKBUFSIZE];

	TCHECK2(pptr[0], BGP_ROUTE_REFRESH_SIZE);


        if (len<BGP_ROUTE_REFRESH_SIZE)
            return;

        bgp_route_refresh_header = (const struct bgp_route_refresh *)pptr;

        printf("\n\t  AFI %s (%u), SAFI %s (%u)",
               tok2strbuf(af_values,"Unknown",


			  EXTRACT_16BITS(&bgp_route_refresh_header->afi),
			  tokbuf, sizeof(tokbuf)),
               EXTRACT_16BITS(&bgp_route_refresh_header->afi),
               tok2strbuf(bgp_safi_values,"Unknown",
			  bgp_route_refresh_header->safi,
			  tokbuf2, sizeof(tokbuf2)),
               bgp_route_refresh_header->safi);

        if (vflag > 1) {
            TCHECK2(*pptr, len);
            print_unknown_data(pptr,"\n\t  ", len);
        }

        return;
trunc:
	printf("[|BGP]");
}
