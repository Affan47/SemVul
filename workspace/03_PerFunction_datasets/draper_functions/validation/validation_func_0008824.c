qxl_crtc_page_flip(struct drm_crtc *crtc,
                              struct drm_framebuffer *fb,
                              struct drm_pending_vblank_event *event,
                              uint32_t page_flip_flags)
{
	struct drm_device *dev = crtc->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct qxl_crtc *qcrtc = to_qxl_crtc(crtc);
	struct qxl_framebuffer *qfb_src = to_qxl_framebuffer(fb);
	struct qxl_framebuffer *qfb_old = to_qxl_framebuffer(crtc->primary->fb);
	struct qxl_bo *bo_old = gem_to_qxl_bo(qfb_old->obj);
	struct qxl_bo *bo = gem_to_qxl_bo(qfb_src->obj);
	unsigned long flags;
	struct drm_clip_rect norect = {
	    .x1 = 0,
	    .y1 = 0,
	    .x2 = fb->width,
	    .y2 = fb->height
	};
	int inc = 1;
	int one_clip_rect = 1;
	int ret = 0;

	crtc->primary->fb = fb;
	bo_old->is_primary = false;
	bo->is_primary = true;

	ret = qxl_bo_reserve(bo, false);
	if (ret)
		return ret;
	ret = qxl_bo_pin(bo, bo->type, NULL);
	qxl_bo_unreserve(bo);
	if (ret)
		return ret;

	qxl_draw_dirty_fb(qdev, qfb_src, bo, 0, 0,
			  &norect, one_clip_rect, inc);

	drm_vblank_get(dev, qcrtc->index);

	if (event) {
		spin_lock_irqsave(&dev->event_lock, flags);
		drm_send_vblank_event(dev, qcrtc->index, event);
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}
	drm_vblank_put(dev, qcrtc->index);

	ret = qxl_bo_reserve(bo, false);
	if (!ret) {
		qxl_bo_unpin(bo);
		qxl_bo_unreserve(bo);
	}

	return 0;
}
