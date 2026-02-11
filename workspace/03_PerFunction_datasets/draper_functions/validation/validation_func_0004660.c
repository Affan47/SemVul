exynos4_jpeg_device_run(void *priv)
{
	struct s5p_jpeg_ctx *ctx = priv;
	struct s5p_jpeg *jpeg = ctx->jpeg;
	unsigned int bitstream_size;
	unsigned long flags;

	spin_lock_irqsave(&jpeg->slock, flags);

	if (ctx->mode == S5P_JPEG_ENCODE) {
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_interrupt(jpeg->regs, jpeg->variant->version);
		exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

		exynos4_jpeg_set_huff_tbl(jpeg->regs);


		exynos4_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		exynos4_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);

		exynos4_jpeg_set_encode_tbl_select(jpeg->regs,
							ctx->compr_quality);
		exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
							ctx->cap_q.h);

		if (ctx->jpeg->variant->version == SJPEG_EXYNOS4) {
			exynos4_jpeg_set_enc_out_fmt(jpeg->regs,
						     ctx->subsampling);
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->out_q.fmt->fourcc);
		} else {
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->out_q.fmt->fourcc);
		}
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);
		exynos4_jpeg_set_encode_hoff_cnt(jpeg->regs,
							ctx->out_q.fmt->fourcc);
	} else {
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_interrupt(jpeg->regs,
					   jpeg->variant->version);
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);

		if (jpeg->variant->version == SJPEG_EXYNOS5433) {
			exynos4_jpeg_parse_huff_tbl(ctx);
			exynos4_jpeg_parse_decode_h_tbl(ctx);

			exynos4_jpeg_parse_q_tbl(ctx);
			exynos4_jpeg_parse_decode_q_tbl(ctx);

			exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

			exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
					ctx->cap_q.h);
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 16);
		} else {
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 32);
		}

		exynos4_jpeg_set_dec_bitstream_size(jpeg->regs, bitstream_size);
	}

	exynos4_jpeg_set_enc_dec_mode(jpeg->regs, ctx->mode);

	spin_unlock_irqrestore(&jpeg->slock, flags);
}
