i915_execlists(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *engine;
	u32 status_pointer;
	u8 read_pointer;
	u8 write_pointer;
	u32 status;
	u32 ctx_id;
	struct list_head *cursor;
	int i, ret;

	if (!i915.enable_execlists) {
		seq_puts(m, "Logical Ring Contexts are disabled\n");
		return 0;
	}

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	intel_runtime_pm_get(dev_priv);

	for_each_engine(engine, dev_priv) {
		struct drm_i915_gem_request *head_req = NULL;
		int count = 0;

		seq_printf(m, "%s\n", engine->name);

		status = I915_READ(RING_EXECLIST_STATUS_LO(engine));
		ctx_id = I915_READ(RING_EXECLIST_STATUS_HI(engine));
		seq_printf(m, "\tExeclist status: 0x%08X, context: %u\n",
			   status, ctx_id);

		status_pointer = I915_READ(RING_CONTEXT_STATUS_PTR(engine));
		seq_printf(m, "\tStatus pointer: 0x%08X\n", status_pointer);

		read_pointer = engine->next_context_status_buffer;
		write_pointer = GEN8_CSB_WRITE_PTR(status_pointer);
		if (read_pointer > write_pointer)
			write_pointer += GEN8_CSB_ENTRIES;
		seq_printf(m, "\tRead pointer: 0x%08X, write pointer 0x%08X\n",
			   read_pointer, write_pointer);

		for (i = 0; i < GEN8_CSB_ENTRIES; i++) {
			status = I915_READ(RING_CONTEXT_STATUS_BUF_LO(engine, i));
			ctx_id = I915_READ(RING_CONTEXT_STATUS_BUF_HI(engine, i));

			seq_printf(m, "\tStatus buffer %d: 0x%08X, context: %u\n",
				   i, status, ctx_id);
		}

		spin_lock_bh(&engine->execlist_lock);
		list_for_each(cursor, &engine->execlist_queue)
			count++;
		head_req = list_first_entry_or_null(&engine->execlist_queue,
						    struct drm_i915_gem_request,
						    execlist_link);
		spin_unlock_bh(&engine->execlist_lock);

		seq_printf(m, "\t%d requests in queue\n", count);
		if (head_req) {
			seq_printf(m, "\tHead request id: %u\n",
				   intel_execlists_ctx_id(head_req->ctx, engine));
			seq_printf(m, "\tHead request tail: %u\n",
				   head_req->tail);
		}

		seq_putc(m, '\n');
	}

	intel_runtime_pm_put(dev_priv);
	mutex_unlock(&dev->struct_mutex);

	return 0;
}
