tn3270e_subneg_send(unsigned char op, unsigned long funcs)
{
	unsigned char proto_buf[7 + 32];
	int proto_len;
	int i;


	(void) memcpy(proto_buf, functions_req, 4);
	proto_buf[4] = op;
	proto_len = 5;
	for (i = 0; i < 32; i++) {
		if (funcs & E_OPT(i))
			proto_buf[proto_len++] = i;
	}


	proto_buf[proto_len++] = IAC;
	proto_buf[proto_len++] = SE;
	net_rawout(proto_buf, proto_len);


	trace_dsn("SENT %s %s FUNCTIONS %s %s %s\n",
	    cmd(SB), opt(TELOPT_TN3270E),
	    (op == TN3270E_OP_REQUEST)? "REQUEST": "IS",
	    tn3270e_function_names(proto_buf + 5, proto_len - 7),
	    cmd(SE));
}
