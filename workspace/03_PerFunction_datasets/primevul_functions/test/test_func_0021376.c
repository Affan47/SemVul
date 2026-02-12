static lzw_result lzw__clear_codes(
		struct lzw_ctx *ctx,
		const uint8_t ** const stack_pos_out)
{
	uint32_t code;
	uint8_t *stack_pos;


	ctx->current_code_size = ctx->initial_code_size + 1;
	ctx->current_code_size_max = (1 << ctx->current_code_size) - 1;;
	ctx->current_entry = (1 << ctx->initial_code_size) + 2;


	do {
		lzw_result res = lzw__next_code(&ctx->input,
				ctx->current_code_size, &code);
		if (res != LZW_OK) {
			return res;
		}
	} while (code == ctx->clear_code);


	if (code > ctx->clear_code) {
		return LZW_BAD_ICODE;
	}


	ctx->previous_code = code;
	ctx->previous_code_first = code;


	stack_pos = ctx->stack_base;
	*stack_pos++ = code;

	*stack_pos_out = stack_pos;
	return LZW_OK;
}
