libmpq__do_decompress_pkzip(uint8_t *work_buf, void *param) {


	pkzip_cmp_s *mpq_pkzip = (pkzip_cmp_s *)work_buf;


	memset(mpq_pkzip, 0, sizeof(pkzip_cmp_s));


	mpq_pkzip->read_buf   = data_read_input;
	mpq_pkzip->write_buf  = data_write_output;
	mpq_pkzip->param      = param;
	mpq_pkzip->in_pos     = sizeof(mpq_pkzip->in_buf);
	mpq_pkzip->in_bytes   = mpq_pkzip->read_buf((char *)mpq_pkzip->in_buf, &mpq_pkzip->in_pos, mpq_pkzip->param);


	if (mpq_pkzip->in_bytes <= 4) {
		return LIBMPQ_PKZIP_CMP_BAD_DATA;
	}


	mpq_pkzip->cmp_type   = mpq_pkzip->in_buf[0];


	mpq_pkzip->dsize_bits = mpq_pkzip->in_buf[1];


	mpq_pkzip->bit_buf    = mpq_pkzip->in_buf[2];


	mpq_pkzip->extra_bits = 0;


	mpq_pkzip->in_pos     = 3;


	if (4 > mpq_pkzip->dsize_bits || mpq_pkzip->dsize_bits > 6) {
		return LIBMPQ_PKZIP_CMP_INV_DICTSIZE;
	}


	mpq_pkzip->dsize_mask = 0xFFFF >> (0x10 - mpq_pkzip->dsize_bits);


	if (mpq_pkzip->cmp_type != LIBMPQ_PKZIP_CMP_BINARY) {


		if (mpq_pkzip->cmp_type != LIBMPQ_PKZIP_CMP_ASCII) {
			return LIBMPQ_PKZIP_CMP_INV_MODE;
		}


		memcpy(mpq_pkzip->bits_asc, pkzip_bits_asc, sizeof(mpq_pkzip->bits_asc));
		generate_tables_ascii(mpq_pkzip);
	}


	memcpy(mpq_pkzip->slen_bits, pkzip_slen_bits, sizeof(mpq_pkzip->slen_bits));
	generate_tables_decode(0x10, mpq_pkzip->slen_bits, pkzip_len_code, mpq_pkzip->pos2);


	memcpy(mpq_pkzip->clen_bits, pkzip_clen_bits, sizeof(mpq_pkzip->clen_bits));
	memcpy(mpq_pkzip->len_base, pkzip_len_base, sizeof(mpq_pkzip->len_base));
	memcpy(mpq_pkzip->dist_bits, pkzip_dist_bits, sizeof(mpq_pkzip->dist_bits));
	generate_tables_decode(0x40, mpq_pkzip->dist_bits, pkzip_dist_code, mpq_pkzip->pos1);


	if (expand(mpq_pkzip) != 0x306) {
		return LIBMPQ_PKZIP_CMP_NO_ERROR;
	}


	return LIBMPQ_PKZIP_CMP_ABORT;
}
