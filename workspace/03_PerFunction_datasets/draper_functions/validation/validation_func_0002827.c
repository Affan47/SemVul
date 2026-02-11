net_output(void)
{
	static unsigned char *xobuf = NULL;
	static int xobuf_len = 0;
	int need_resize = 0;
	unsigned char *nxoptr, *xoptr;

#if defined(X3270_TN3270E)
#define BSTART	((IN_TN3270E || IN_SSCP) ? obuf_base : obuf)
#else
#define BSTART	obuf
#endif

#if defined(X3270_TN3270E)

	if (IN_TN3270E || IN_SSCP) {
		tn3270e_header *h = (tn3270e_header *)obuf_base;


		if (response_required == TN3270E_RSF_ALWAYS_RESPONSE) {
			tn3270e_ack();
			response_required = TN3270E_RSF_NO_RESPONSE;
		}


		h->data_type = IN_TN3270E ?
			TN3270E_DT_3270_DATA : TN3270E_DT_SSCP_LU_DATA;
		h->request_flag = 0;
		h->response_flag = 0;
		h->seq_number[0] = (e_xmit_seq >> 8) & 0xff;
		h->seq_number[1] = e_xmit_seq & 0xff;

		trace_dsn("SENT TN3270E(%s NO-RESPONSE %u)\n",
			IN_TN3270E ? "3270-DATA" : "SSCP-LU-DATA", e_xmit_seq);
		if (e_funcs & E_OPT(TN3270E_FUNC_RESPONSES))
			e_xmit_seq = (e_xmit_seq + 1) & 0x7fff;
	}
#endif


	while (xobuf_len <  (obptr - BSTART + 1) * 2) {
		xobuf_len += BUFSZ;
		need_resize++;
	}
	if (need_resize) {
		Replace(xobuf, (unsigned char *)Malloc(xobuf_len));
	}


	xoptr = xobuf;
	nxoptr = BSTART;
	while (nxoptr < obptr) {
		if ((*xoptr++ = *nxoptr++) == IAC) {
			*xoptr++ = IAC;
		}
	}


	*xoptr++ = IAC;
	*xoptr++ = EOR;
	net_rawout(xobuf, xoptr - xobuf);

	trace_dsn("SENT EOR\n");
	ns_rsent++;
#undef BSTART
}
