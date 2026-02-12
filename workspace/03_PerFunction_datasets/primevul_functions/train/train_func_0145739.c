static int eb_move_to_gpu(struct i915_execbuffer *eb)
{
	const unsigned int count = eb->buffer_count;
	unsigned int i;
	int err;

	for (i = 0; i < count; i++) {
		unsigned int flags = eb->flags[i];
		struct i915_vma *vma = eb->vma[i];
		struct drm_i915_gem_object *obj = vma->obj;

		if (flags & EXEC_OBJECT_CAPTURE) {
			struct i915_capture_list *capture;

			capture = kmalloc(sizeof(*capture), GFP_KERNEL);
			if (unlikely(!capture))
				return -ENOMEM;

			capture->next = eb->request->capture_list;
			capture->vma = eb->vma[i];
			eb->request->capture_list = capture;
		}


		if (unlikely(obj->cache_dirty & ~obj->cache_coherent)) {
			if (i915_gem_clflush_object(obj, 0))
				flags &= ~EXEC_OBJECT_ASYNC;
		}

		if (flags & EXEC_OBJECT_ASYNC)
			continue;

		err = i915_request_await_object
			(eb->request, obj, flags & EXEC_OBJECT_WRITE);
		if (err)
			return err;
	}

	for (i = 0; i < count; i++) {
		unsigned int flags = eb->flags[i];
		struct i915_vma *vma = eb->vma[i];

		err = i915_vma_move_to_active(vma, eb->request, flags);
		if (unlikely(err)) {
			i915_request_skip(eb->request, err);
			return err;
		}

		__eb_unreserve_vma(vma, flags);
		vma->exec_flags = NULL;

		if (unlikely(flags & __EXEC_OBJECT_HAS_REF))
			i915_vma_put(vma);
	}
	eb->exec = NULL;


	i915_gem_chipset_flush(eb->i915);

	return 0;
}
