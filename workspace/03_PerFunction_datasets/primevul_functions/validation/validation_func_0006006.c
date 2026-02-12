cardos_decipher(struct sc_card *card,
		const u8 * crgram, size_t crgram_len,
		u8 * out, size_t outlen)
{
	cardos_data_t* priv = (cardos_data_t*)card->drv_data;
	int r;
	size_t card_max_send_size = card->max_send_size;
	size_t reader_max_send_size = card->reader->max_send_size;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);


	if (card->type == SC_CARD_TYPE_CARDOS_V5_0 || card->type == SC_CARD_TYPE_CARDOS_V5_3) {

		r = iso_ops->decipher(card, crgram, crgram_len, out, outlen);


		if (r > 0 && priv->sec_env->algorithm_flags & SC_ALGORITHM_RSA_RAW) {
			size_t rsize = r;


			if (rsize == crgram_len - 1 && rsize < outlen) {
				memmove(out+1, out, rsize);
				out[0] =0x00;
				r++;
			}
		}

		SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
	}

	if (sc_get_max_send_size(card) < crgram_len + 1) {


		card->max_send_size = crgram_len + 1;
		card->reader->max_send_size = crgram_len + 1;
	}

	r = iso_ops->decipher(card, crgram, crgram_len, out, outlen);


	card->max_send_size = card_max_send_size;
	card->reader->max_send_size = reader_max_send_size;

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}
