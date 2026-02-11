drm_intel_gem_bo_set_tiling(drm_intel_bo *bo, uint32_t * tiling_mode,
			    uint32_t stride)
{
	drm_intel_bufmgr_gem *bufmgr_gem = (drm_intel_bufmgr_gem *) bo->bufmgr;
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	int ret;


	if (*tiling_mode == I915_TILING_NONE)
		stride = 0;

	ret = drm_intel_gem_bo_set_tiling_internal(bo, *tiling_mode, stride);
	if (ret == 0)
		drm_intel_bo_gem_set_in_aperture_size(bufmgr_gem, bo_gem);

	*tiling_mode = bo_gem->tiling_mode;
	return ret;
}
