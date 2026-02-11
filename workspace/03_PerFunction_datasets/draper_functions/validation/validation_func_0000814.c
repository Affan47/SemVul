isaac64_gen_keystream(void *ctx_, size_t offset, uint8_t *obuf, size_t olen)
{
    isaac64_context *ctx = ctx_;
    size_t offset_RANDSIZ, offset_64b, offset_rem;
    uint8_t buf[8];
    uint8_t *limit = obuf + olen;

    if (offset < ctx->offset)
        abort();

    offset_RANDSIZ = offset / RANDSIZB;
    while (ctx->offset < offset_RANDSIZ)
    {
        isaac64_core(ctx);
        ctx->offset += RANDSIZB;
    }

    offset_64b = (offset % RANDSIZB) / 8;
    offset_rem = (offset % RANDSIZB) % 8;
    for (;;)
    {
        for (; offset_64b < RANDSIZ; offset_64b++)
        {
            cpu_to_be64(buf, ctx->randrsl[offset_64b]);
            for (; offset_rem < 8; offset_rem++)
            {
                *obuf++ = buf[offset_rem];
                if (obuf >= limit)
                    goto out;
            }
            offset_rem = 0;
        }
        offset_64b = 0;
        isaac64_core(ctx);
    }
 out:
    ctx->offset = offset + olen;


    if (ctx->offset % RANDSIZB == 0)
        isaac64_core(ctx);
}
