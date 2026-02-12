static int idprime_select_index(sc_card_t *card)
{
	int r;
	sc_file_t *file = NULL;
	sc_path_t index_path;


	r = idprime_select_idprime(card);
	if (r != SC_SUCCESS) {
		LOG_FUNC_RETURN(card->ctx, r);
	}


	sc_format_path("0101", &index_path);
	r = iso_ops->select_file(card, &index_path, &file);
	if (r == SC_SUCCESS) {
		r = file->size;
	}
	sc_file_free(file);

	if (r <= 0 ||  r > MAX_FILE_SIZE) {
		r = SC_ERROR_INVALID_DATA;
	}
	return r;
}
