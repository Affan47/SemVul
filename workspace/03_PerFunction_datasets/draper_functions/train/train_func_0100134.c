bt_final(torrent_ctx *ctx, unsigned char result[20])
{
	if (ctx->index > 0) {
		bt_store_piece_sha1(ctx);
	}

	bt_generate_torrent(ctx);
	if (result) memcpy(result, ctx->btih, btih_hash_size);
}
