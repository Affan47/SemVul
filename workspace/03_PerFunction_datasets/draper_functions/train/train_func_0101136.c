drm_intel_bo_mrb_exec(drm_intel_bo *bo, int used,
		drm_clip_rect_t *cliprects, int num_cliprects, int DR4,
		unsigned int rings)
{
	if (bo->bufmgr->bo_mrb_exec)
		return bo->bufmgr->bo_mrb_exec(bo, used,
					cliprects, num_cliprects, DR4,
					rings);

	switch (rings) {
	case I915_EXEC_DEFAULT:
	case I915_EXEC_RENDER:
		return bo->bufmgr->bo_exec(bo, used,
					   cliprects, num_cliprects, DR4);
	default:
		return -ENODEV;
	}
}
