psb_gem_create(struct drm_file *file, struct drm_device *dev, u64 size,
		   u32 *handlep, int stolen, u32 align)
{
	struct gtt_range *r;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);


	r = psb_gtt_alloc_range(dev, size, "gem", 0, PAGE_SIZE);
	if (r == NULL) {
		dev_err(dev->dev, "no memory for %lld byte GEM object\n", size);
		return -ENOSPC;
	}

	if (drm_gem_object_init(dev, &r->gem, size) != 0) {
		psb_gtt_free_range(dev, r);

		dev_err(dev->dev, "GEM init failed for %lld\n", size);
		return -ENOMEM;
	}

	mapping_set_gfp_mask(r->gem.filp->f_mapping, GFP_KERNEL | __GFP_DMA32);

	ret = drm_gem_handle_create(file, &r->gem, &handle);
	if (ret) {
		dev_err(dev->dev, "GEM handle failed for %p, %lld\n",
							&r->gem, size);
		drm_gem_object_release(&r->gem);
		psb_gtt_free_range(dev, r);
		return ret;
	}

	drm_gem_object_unreference_unlocked(&r->gem);
	*handlep = handle;
	return 0;
}
