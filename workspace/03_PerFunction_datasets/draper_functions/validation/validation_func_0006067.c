md2_finish (md2_t *ctx, void *digest, unsigned int digestlen)
{
  if (ctx == NULL || ctx->magic != MD2_MAGIC
      || digest == NULL || digestlen < MD2_DIGEST_LENGTH)
    {
      errno = EINVAL;
      return (-1);
    }

  _md2_append_padding_and_checksum (ctx);
  memcpy (digest, X, MD2_DIGEST_LENGTH);

  ctx->magic = ~MD2_MAGIC;
  return (MD2_DIGEST_LENGTH);
}
