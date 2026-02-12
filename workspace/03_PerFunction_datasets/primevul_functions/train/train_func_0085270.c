read_compressed(cdk_stream_t inp, size_t pktlen, cdk_pkt_compressed_t c)
{
	if (!inp || !c)
		return CDK_Inv_Value;

	if (DEBUG_PKT)
		_gnutls_write_log("read_compressed: %d octets\n",
				  (int) pktlen);

	c->algorithm = cdk_stream_getc(inp);
	if (c->algorithm > 3)
		return CDK_Inv_Packet;


	if (!pktlen) {
		c->len = 0;
		c->buf = inp;
	}


	return 0;
}
