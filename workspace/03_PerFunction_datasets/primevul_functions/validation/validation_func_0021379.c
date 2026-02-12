static struct pipe_ctx *dcn20_find_secondary_pipe(struct dc *dc,
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		const struct pipe_ctx *primary_pipe)
{
	struct pipe_ctx *secondary_pipe = NULL;

	if (dc && primary_pipe) {
		int j;
		int preferred_pipe_idx = 0;


		if (dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe) {
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe->pipe_idx;
			if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			}
		} else if (dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe) {
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe->pipe_idx;
			if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			}
		}


		if (secondary_pipe == NULL) {
			for (j = dc->res_pool->pipe_count - 1; j >= 0; j--) {
				if (dc->current_state->res_ctx.pipe_ctx[j].top_pipe == NULL) {
					preferred_pipe_idx = j;

					if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
						secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
						secondary_pipe->pipe_idx = preferred_pipe_idx;
						break;
					}
				}
			}
		}


		ASSERT(secondary_pipe);


		if (secondary_pipe == NULL) {
			for (j = dc->res_pool->pipe_count - 1; j >= 0; j--) {
				preferred_pipe_idx = j;

				if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
					secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
					secondary_pipe->pipe_idx = preferred_pipe_idx;
					break;
				}
			}
		}
	}

	return secondary_pipe;
}
