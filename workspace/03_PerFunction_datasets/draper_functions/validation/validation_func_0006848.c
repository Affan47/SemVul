isns_authblock_encode(buf_t *bp, const struct isns_authblk *auth)
{
	if (!buf_put32(bp, auth->iab_bsd)
	 || !buf_put32(bp, auth->iab_length)
	 || !buf_put64(bp, auth->iab_timestamp)
	 || !buf_put32(bp, auth->iab_spi_len)
	 || !buf_put(bp, auth->iab_spi, auth->iab_spi_len)
	 || !buf_put(bp, auth->iab_sig, auth->iab_sig_len))
		return 0;
	return 1;
}
