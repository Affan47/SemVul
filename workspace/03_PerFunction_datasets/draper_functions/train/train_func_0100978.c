imap_open_store_authenticate_p2( imap_store_t *ctx, struct imap_cmd *cmd ATTR_UNUSED, int response )
{
	if (response == RESP_NO)
		imap_open_store_bail( ctx );
	else if (response == RESP_OK)
		socket_start_tls( &ctx->conn, imap_open_store_tlsstarted2 );
}
