i915_gem_do_execbuffer(struct drm_device *dev,
		       struct drm_file *file,
		       struct drm_i915_gem_execbuffer2 *args,
		       struct drm_i915_gem_exec_object2 *exec,
		       struct drm_syncobj **fences)
{
	struct i915_execbuffer eb;
	struct dma_fence *in_fence = NULL;
	struct sync_file *out_fence = NULL;
	int out_fence_fd = -1;
	int err;

	BUILD_BUG_ON(__EXEC_INTERNAL_FLAGS & ~__I915_EXEC_ILLEGAL_FLAGS);
	BUILD_BUG_ON(__EXEC_OBJECT_INTERNAL_FLAGS &
		     ~__EXEC_OBJECT_UNKNOWN_FLAGS);

	eb.i915 = to_i915(dev);
	eb.file = file;
	eb.args = args;
	if (DBG_FORCE_RELOC || !(args->flags & I915_EXEC_NO_RELOC))
		args->flags |= __EXEC_HAS_RELOC;

	eb.exec = exec;
	eb.vma = (struct i915_vma **)(exec + args->buffer_count + 1);
	eb.vma[0] = NULL;
	eb.flags = (unsigned int *)(eb.vma + args->buffer_count + 1);

	eb.invalid_flags = __EXEC_OBJECT_UNKNOWN_FLAGS;
	reloc_cache_init(&eb.reloc_cache, eb.i915);

	eb.buffer_count = args->buffer_count;
	eb.batch_start_offset = args->batch_start_offset;
	eb.batch_len = args->batch_len;

	eb.batch_flags = 0;
	if (args->flags & I915_EXEC_SECURE) {
		if (!drm_is_current_master(file) || !capable(CAP_SYS_ADMIN))
		    return -EPERM;

		eb.batch_flags |= I915_DISPATCH_SECURE;
	}
	if (args->flags & I915_EXEC_IS_PINNED)
		eb.batch_flags |= I915_DISPATCH_PINNED;

	eb.engine = eb_select_engine(eb.i915, file, args);
	if (!eb.engine)
		return -EINVAL;

	if (args->flags & I915_EXEC_FENCE_IN) {
		in_fence = sync_file_get_fence(lower_32_bits(args->rsvd2));
		if (!in_fence)
			return -EINVAL;
	}

	if (args->flags & I915_EXEC_FENCE_OUT) {
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		if (out_fence_fd < 0) {
			err = out_fence_fd;
			goto err_in_fence;
		}
	}

	err = eb_create(&eb);
	if (err)
		goto err_out_fence;

	GEM_BUG_ON(!eb.lut_size);

	err = eb_select_context(&eb);
	if (unlikely(err))
		goto err_destroy;


	intel_runtime_pm_get(eb.i915);

	err = i915_mutex_lock_interruptible(dev);
	if (err)
		goto err_rpm;

	err = eb_relocate(&eb);
	if (err) {


		args->flags &= ~__EXEC_HAS_RELOC;
		goto err_vma;
	}

	if (unlikely(*eb.batch->exec_flags & EXEC_OBJECT_WRITE)) {
		DRM_DEBUG("Attempting to use self-modifying batch buffer\n");
		err = -EINVAL;
		goto err_vma;
	}
	if (eb.batch_start_offset > eb.batch->size ||
	    eb.batch_len > eb.batch->size - eb.batch_start_offset) {
		DRM_DEBUG("Attempting to use out-of-bounds batch\n");
		err = -EINVAL;
		goto err_vma;
	}

	if (eb_use_cmdparser(&eb)) {
		struct i915_vma *vma;

		vma = eb_parse(&eb, drm_is_current_master(file));
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_vma;
		}

		if (vma) {


			eb.batch_flags |= I915_DISPATCH_SECURE;
			eb.batch_start_offset = 0;
			eb.batch = vma;
		}
	}

	if (eb.batch_len == 0)
		eb.batch_len = eb.batch->size - eb.batch_start_offset;


	if (eb.batch_flags & I915_DISPATCH_SECURE) {
		struct i915_vma *vma;


		vma = i915_gem_object_ggtt_pin(eb.batch->obj, NULL, 0, 0, 0);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_vma;
		}

		eb.batch = vma;
	}


	GEM_BUG_ON(eb.reloc_cache.rq);


	eb.request = i915_request_alloc(eb.engine, eb.ctx);
	if (IS_ERR(eb.request)) {
		err = PTR_ERR(eb.request);
		goto err_batch_unpin;
	}

	if (in_fence) {
		err = i915_request_await_dma_fence(eb.request, in_fence);
		if (err < 0)
			goto err_request;
	}

	if (fences) {
		err = await_fence_array(&eb, fences);
		if (err)
			goto err_request;
	}

	if (out_fence_fd != -1) {
		out_fence = sync_file_create(&eb.request->fence);
		if (!out_fence) {
			err = -ENOMEM;
			goto err_request;
		}
	}


	eb.request->batch = eb.batch;

	trace_i915_request_queue(eb.request, eb.batch_flags);
	err = eb_submit(&eb);
err_request:
	i915_request_add(eb.request);
	add_to_client(eb.request, file);

	if (fences)
		signal_fence_array(&eb, fences);

	if (out_fence) {
		if (err == 0) {
			fd_install(out_fence_fd, out_fence->file);
			args->rsvd2 &= GENMASK_ULL(31, 0);
			args->rsvd2 |= (u64)out_fence_fd << 32;
			out_fence_fd = -1;
		} else {
			fput(out_fence->file);
		}
	}

err_batch_unpin:
	if (eb.batch_flags & I915_DISPATCH_SECURE)
		i915_vma_unpin(eb.batch);
err_vma:
	if (eb.exec)
		eb_release_vmas(&eb);
	mutex_unlock(&dev->struct_mutex);
err_rpm:
	intel_runtime_pm_put(eb.i915);
	i915_gem_context_put(eb.ctx);
err_destroy:
	eb_destroy(&eb);
err_out_fence:
	if (out_fence_fd != -1)
		put_unused_fd(out_fence_fd);
err_in_fence:
	dma_fence_put(in_fence);
	return err;
}
