bench_cell_ops(void)
{
  const int iters = 1<<16;
  int i;


  or_circuit_t *or_circ = tor_malloc_zero(sizeof(or_circuit_t));
  cell_t *cell = tor_malloc(sizeof(cell_t));
  int outbound;
  uint64_t start, end;

  crypto_rand((char*)cell->payload, sizeof(cell->payload));


  or_circ->_base.magic = OR_CIRCUIT_MAGIC;
  or_circ->_base.purpose = CIRCUIT_PURPOSE_OR;


  or_circ->p_crypto = crypto_cipher_new();
  crypto_cipher_generate_key(or_circ->p_crypto);
  crypto_cipher_encrypt_init_cipher(or_circ->p_crypto);
  or_circ->n_crypto = crypto_cipher_new();
  crypto_cipher_generate_key(or_circ->n_crypto);
  crypto_cipher_encrypt_init_cipher(or_circ->n_crypto);
  or_circ->p_digest = crypto_digest_new();
  or_circ->n_digest = crypto_digest_new();

  reset_perftime();

  for (outbound = 0; outbound <= 1; ++outbound) {
    cell_direction_t d = outbound ? CELL_DIRECTION_OUT : CELL_DIRECTION_IN;
    start = perftime();
    for (i = 0; i < iters; ++i) {
      char recognized = 0;
      crypt_path_t *layer_hint = NULL;
      relay_crypt(TO_CIRCUIT(or_circ), cell, d, &layer_hint, &recognized);
    }
    end = perftime();
    printf("%sbound cells: %.2f ns per cell. (%.2f ns per byte of payload)\n",
           outbound?"Out":" In",
           NANOCOUNT(start,end,iters),
           NANOCOUNT(start,end,iters*CELL_PAYLOAD_SIZE));
  }

  crypto_digest_free(or_circ->p_digest);
  crypto_digest_free(or_circ->n_digest);
  crypto_cipher_free(or_circ->p_crypto);
  crypto_cipher_free(or_circ->n_crypto);
  tor_free(or_circ);
  tor_free(cell);
}
