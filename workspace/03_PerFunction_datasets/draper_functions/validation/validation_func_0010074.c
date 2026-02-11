ast_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct ast_private *ast = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct ast_framebuffer *ast_fb;
	struct ast_bo *bo;
	int ret;
	u64 gpu_addr;


	if (!atomic && fb) {
		ast_fb = to_ast_framebuffer(fb);
		obj = ast_fb->obj;
		bo = gem_to_ast_bo(obj);
		ret = ast_bo_reserve(bo, false);
		if (ret)
			return ret;
		ast_bo_push_sysram(bo);
		ast_bo_unreserve(bo);
	}

	ast_fb = to_ast_framebuffer(crtc->primary->fb);
	obj = ast_fb->obj;
	bo = gem_to_ast_bo(obj);

	ret = ast_bo_reserve(bo, false);
	if (ret)
		return ret;

	ret = ast_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	if (ret) {
		ast_bo_unreserve(bo);
		return ret;
	}

	if (&ast->fbdev->afb == ast_fb) {

		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret)
			DRM_ERROR("failed to kmap fbcon\n");
		else
			ast_fbdev_set_base(ast, gpu_addr);
	}
	ast_bo_unreserve(bo);

	ast_set_start_address_crt1(crtc, (u32)gpu_addr);

	return 0;
}
