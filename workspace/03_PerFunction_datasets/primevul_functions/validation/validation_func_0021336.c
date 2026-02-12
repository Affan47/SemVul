enum dc_status dcn20_build_mapped_resource(const struct dc *dc, struct dc_state *context, struct dc_stream_state *stream)
{
	enum dc_status status = DC_OK;
	struct pipe_ctx *pipe_ctx = resource_get_head_pipe_for_stream(&context->res_ctx, stream);


	if (!pipe_ctx)
		return DC_ERROR_UNEXPECTED;


	status = build_pipe_hw_param(pipe_ctx);

	return status;
}
