owrite(BuildCtx *ctx, const void *ptr, size_t sz)
{
  if (fwrite(ptr, 1, sz, ctx->fp) != sz) {
    fprintf(stderr, "Error: cannot write to output file: %s\n",
	    strerror(errno));
    exit(1);
  }
}
