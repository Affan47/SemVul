s5p_mfc_enc_calc_src_size_v6(struct s5p_mfc_ctx *ctx)
{
	unsigned int mb_width, mb_height;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);

	ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN_V6);
	ctx->luma_size = ALIGN((mb_width * mb_height) * 256, 256);
	ctx->chroma_size = ALIGN((mb_width * mb_height) * 128, 256);


	if (IS_MFCV7_PLUS(ctx->dev)) {
		ctx->luma_size += MFC_LUMA_PAD_BYTES_V7;
		ctx->chroma_size += MFC_CHROMA_PAD_BYTES_V7;
	}
}
