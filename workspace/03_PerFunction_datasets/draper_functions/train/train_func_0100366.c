init_hmac (HMAC_CTX *ctx, const EVP_MD *digest,
	   struct key *key, const struct key_type *kt, const char *prefix)
{
  struct gc_arena gc = gc_new ();

  HMAC_CTX_init (ctx);
  HMAC_Init_ex (ctx, key->hmac, kt->hmac_length, digest, NULL);
  msg (D_HANDSHAKE,
       "%s: Using %d bit message hash '%s' for HMAC authentication",
       prefix, HMAC_size (ctx) * 8, OBJ_nid2sn (EVP_MD_type (digest)));


  ASSERT (HMAC_size (ctx) <= kt->hmac_length);

  dmsg (D_SHOW_KEYS, "%s: HMAC KEY: %s", prefix,
       format_hex (key->hmac, kt->hmac_length, 0, &gc));
  dmsg (D_CRYPTO_DEBUG, "%s: HMAC size=%d block_size=%d",
       prefix,
       EVP_MD_size (digest),
       EVP_MD_block_size (digest));

  gc_free (&gc);
}
