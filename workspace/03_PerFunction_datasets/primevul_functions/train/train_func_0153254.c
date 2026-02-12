getkey_next (getkey_ctx_t ctx, PKT_public_key *pk, kbnode_t *ret_keyblock)
{
  int rc;

  rc = lookup (ctx, ret_keyblock, ctx->want_secret);
  if (!rc && pk && ret_keyblock)
    pk_from_block (ctx, pk, *ret_keyblock);

  return rc;
}
