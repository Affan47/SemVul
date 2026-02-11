fio_sha256_update(struct fio_sha256_ctx *sctx, const uint8_t *data,
		       unsigned int len)
{
	unsigned int partial, done;
	const uint8_t *src;

	partial = sctx->count & 0x3f;
	sctx->count += len;
	done = 0;
	src = data;

	if ((partial + len) > 63) {
		if (partial) {
			done = -partial;
			memcpy(sctx->buf + partial, data, done + 64);
			src = sctx->buf;
		}

		do {
			sha256_transform(sctx->state, src);
			done += 64;
			src = data + done;
		} while (done + 63 < len);

		partial = 0;
	}
	memcpy(sctx->buf + partial, src, len - done);
}
