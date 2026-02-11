radeon_crtc_cursor_set2(struct drm_crtc *crtc,
			    struct drm_file *file_priv,
			    uint32_t handle,
			    uint32_t width,
			    uint32_t height,
			    int32_t hot_x,
			    int32_t hot_y)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_device *rdev = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct radeon_bo *robj;
	int ret;

	if (!handle) {

		radeon_hide_cursor(crtc);
		obj = NULL;
		goto unpin;
	}

	if ((width > radeon_crtc->max_cursor_width) ||
	    (height > radeon_crtc->max_cursor_height)) {
		DRM_ERROR("bad cursor width or height %d x %d\n", width, height);
		return -EINVAL;
	}

	obj = drm_gem_object_lookup(crtc->dev, file_priv, handle);
	if (!obj) {
		DRM_ERROR("Cannot find cursor object %x for crtc %d\n", handle, radeon_crtc->crtc_id);
		return -ENOENT;
	}

	robj = gem_to_radeon_bo(obj);
	ret = radeon_bo_reserve(robj, false);
	if (ret != 0) {
		drm_gem_object_unreference_unlocked(obj);
		return ret;
	}

	ret = radeon_bo_pin_restricted(robj, RADEON_GEM_DOMAIN_VRAM,
				       ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27,
				       &radeon_crtc->cursor_addr);
	radeon_bo_unreserve(robj);
	if (ret) {
		DRM_ERROR("Failed to pin new cursor BO (%d)\n", ret);
		drm_gem_object_unreference_unlocked(obj);
		return ret;
	}

	radeon_lock_cursor(crtc, true);

	if (width != radeon_crtc->cursor_width ||
	    height != radeon_crtc->cursor_height ||
	    hot_x != radeon_crtc->cursor_hot_x ||
	    hot_y != radeon_crtc->cursor_hot_y) {
		int x, y;

		x = radeon_crtc->cursor_x + radeon_crtc->cursor_hot_x - hot_x;
		y = radeon_crtc->cursor_y + radeon_crtc->cursor_hot_y - hot_y;

		radeon_crtc->cursor_width = width;
		radeon_crtc->cursor_height = height;
		radeon_crtc->cursor_hot_x = hot_x;
		radeon_crtc->cursor_hot_y = hot_y;

		radeon_cursor_move_locked(crtc, x, y);
	}

	radeon_show_cursor(crtc);

	radeon_lock_cursor(crtc, false);

unpin:
	if (radeon_crtc->cursor_bo) {
		struct radeon_bo *robj = gem_to_radeon_bo(radeon_crtc->cursor_bo);
		ret = radeon_bo_reserve(robj, false);
		if (likely(ret == 0)) {
			radeon_bo_unpin(robj);
			radeon_bo_unreserve(robj);
		}
		drm_gem_object_unreference_unlocked(radeon_crtc->cursor_bo);
	}

	radeon_crtc->cursor_bo = obj;
	return 0;
}
