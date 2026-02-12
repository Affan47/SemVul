static int steal_hw_id(struct drm_i915_private *i915)
{
	struct i915_gem_context *ctx, *cn;
	LIST_HEAD(pinned);
	int id = -ENOSPC;

	lockdep_assert_held(&i915->contexts.mutex);

	list_for_each_entry_safe(ctx, cn,
				 &i915->contexts.hw_id_list, hw_id_link) {
		if (atomic_read(&ctx->hw_id_pin_count)) {
			list_move_tail(&ctx->hw_id_link, &pinned);
			continue;
		}

		GEM_BUG_ON(!ctx->hw_id);
		list_del_init(&ctx->hw_id_link);
		id = ctx->hw_id;
		break;
	}


	list_splice_tail(&pinned, &i915->contexts.hw_id_list);
	return id;
}
