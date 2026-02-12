static void rotate_ctx(struct perf_event_context *ctx, struct perf_event *event)
{


	if (ctx->rotate_disable)
		return;

	perf_event_groups_delete(&ctx->flexible_groups, event);
	perf_event_groups_insert(&ctx->flexible_groups, event);
}
