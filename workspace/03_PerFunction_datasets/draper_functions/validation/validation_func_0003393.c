mrg_step_install_table(struct bgtask *unused_h, void *u, int unused_ticks)
{
	struct merge_context *ctx = u;

	(void) unused_h;
	(void) unused_ticks;
	g_assert(MERGE_MAGIC == ctx->magic);


	if (settings_is_ultra()) {
		struct routing_table *mt;
		if (ctx->slots != 0)
			mt = qrt_create("Merged table",
				cast_to_pointer(ctx->arena), ctx->slots, LOCAL_INFINITY);
		else {
			g_assert(ctx->arena == NULL);
			mt = qrt_empty_table("Empty merged table");
		}
		ctx->arena = NULL;
		install_merged_table(mt);
	}

	return BGR_DONE;
}
