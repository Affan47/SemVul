decode_2d_br01(struct drm_intel_decode *ctx)
{
	const char *format;
	switch ((ctx->data[1] >> 24) & 0x3) {
	case 0:
		format = "8";
		break;
	case 1:
		format = "565";
		break;
	case 2:
		format = "1555";
		break;
	case 3:
		format = "8888";
		break;
	}

	instr_out(ctx, 1,
		  "format %s, pitch %d, rop 0x%02x, "
		  "clipping %sabled, %s%s \n",
		  format,
		  (short)(ctx->data[1] & 0xffff),
		  (ctx->data[1] >> 16) & 0xff,
		  ctx->data[1] & (1 << 30) ? "en" : "dis",
		  ctx->data[1] & (1 << 31) ? "solid pattern enabled, " : "",
		  ctx->data[1] & (1 << 31) ?
		  "mono pattern transparency enabled, " : "");

}
