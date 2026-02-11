drm_intel_bo_set_tiling(drm_intel_bo *bo, uint32_t * tiling_mode,
			uint32_t stride)
{
	if (bo->bufmgr->bo_set_tiling)
		return bo->bufmgr->bo_set_tiling(bo, tiling_mode, stride);

	*tiling_mode = I915_TILING_NONE;
	return 0;
}
