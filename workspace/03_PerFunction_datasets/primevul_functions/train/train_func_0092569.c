static int idprime_select_file(sc_card_t *card, const sc_path_t *in_path, sc_file_t **file_out)
{
	int r, len;
	idprime_private_data_t * priv = card->drv_data;
	u8 data[HEADER_LEN];
	size_t data_len = HEADER_LEN;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);


	if (priv->cache_buf) {
		free(priv->cache_buf);
		priv->cache_buf = NULL;
	}
	priv->cache_buf_len = 0;
	priv->cached = 0;

	r = iso_ops->select_file(card, in_path, file_out);
	if (r == SC_SUCCESS && file_out != NULL) {


		len = iso_ops->read_binary(card, 0, data, data_len, 0);
		if (len == HEADER_LEN && data[0] == 0x01 && data[1] == 0x00) {

			priv->file_size = (*file_out)->size;

			(*file_out)->size = (data[3]<<8) | data[2];
		}
	}

	return r;
}
