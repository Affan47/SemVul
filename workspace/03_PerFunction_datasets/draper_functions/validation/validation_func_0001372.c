i915_gem_pageflip_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc;
	int ret;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	for_each_intel_crtc(dev, crtc) {
		const char pipe = pipe_name(crtc->pipe);
		const char plane = plane_name(crtc->plane);
		struct intel_unpin_work *work;

		spin_lock_irq(&dev->event_lock);
		work = crtc->unpin_work;
		if (work == NULL) {
			seq_printf(m, "No flip due on pipe %c (plane %c)\n",
				   pipe, plane);
		} else {
			u32 addr;

			if (atomic_read(&work->pending) < INTEL_FLIP_COMPLETE) {
				seq_printf(m, "Flip queued on pipe %c (plane %c)\n",
					   pipe, plane);
			} else {
				seq_printf(m, "Flip pending (waiting for vsync) on pipe %c (plane %c)\n",
					   pipe, plane);
			}
			if (work->flip_queued_req) {
				struct intel_engine_cs *engine = i915_gem_request_get_engine(work->flip_queued_req);

				seq_printf(m, "Flip queued on %s at seqno %x, next seqno %x [current breadcrumb %x], completed? %d\n",
					   engine->name,
					   i915_gem_request_get_seqno(work->flip_queued_req),
					   dev_priv->next_seqno,
					   engine->get_seqno(engine),
					   i915_gem_request_completed(work->flip_queued_req, true));
			} else
				seq_printf(m, "Flip not associated with any ring\n");
			seq_printf(m, "Flip queued on frame %d, (was ready on frame %d), now %d\n",
				   work->flip_queued_vblank,
				   work->flip_ready_vblank,
				   drm_crtc_vblank_count(&crtc->base));
			if (work->enable_stall_check)
				seq_puts(m, "Stall check enabled, ");
			else
				seq_puts(m, "Stall check waiting for page flip ioctl, ");
			seq_printf(m, "%d prepares\n", atomic_read(&work->pending));

			if (INTEL_INFO(dev)->gen >= 4)
				addr = I915_HI_DISPBASE(I915_READ(DSPSURF(crtc->plane)));
			else
				addr = I915_READ(DSPADDR(crtc->plane));
			seq_printf(m, "Current scanout address 0x%08x\n", addr);

			if (work->pending_flip_obj) {
				seq_printf(m, "New framebuffer address 0x%08lx\n", (long)work->gtt_offset);
				seq_printf(m, "MMIO update completed? %d\n",  addr == work->gtt_offset);
			}
		}
		spin_unlock_irq(&dev->event_lock);
	}

	mutex_unlock(&dev->struct_mutex);

	return 0;
}
