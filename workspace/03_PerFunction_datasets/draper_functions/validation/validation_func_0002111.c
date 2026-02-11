r300_emit_cliprects(drm_radeon_private_t *dev_priv,
			       drm_radeon_kcmd_buffer_t *cmdbuf, int n)
{
	struct drm_clip_rect box;
	int nr;
	int i;
	RING_LOCALS;

	nr = cmdbuf->nbox - n;
	if (nr > R300_SIMULTANEOUS_CLIPRECTS)
		nr = R300_SIMULTANEOUS_CLIPRECTS;

	DRM_DEBUG("%i cliprects\n", nr);

	if (nr) {
		BEGIN_RING(6 + nr * 2);
		OUT_RING(CP_PACKET0(R300_RE_CLIPRECT_TL_0, nr * 2 - 1));

		for (i = 0; i < nr; ++i) {
			if (copy_from_user
			    (&box, &cmdbuf->boxes[n + i], sizeof(box))) {
				DRM_ERROR("copy cliprect faulted\n");
				return -EFAULT;
			}

			box.x2--;
			box.y2--;

			if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV515) {
				box.x1 = (box.x1) &
					R300_CLIPRECT_MASK;
				box.y1 = (box.y1) &
					R300_CLIPRECT_MASK;
				box.x2 = (box.x2) &
					R300_CLIPRECT_MASK;
				box.y2 = (box.y2) &
					R300_CLIPRECT_MASK;
			} else {
				box.x1 = (box.x1 + R300_CLIPRECT_OFFSET) &
					R300_CLIPRECT_MASK;
				box.y1 = (box.y1 + R300_CLIPRECT_OFFSET) &
					R300_CLIPRECT_MASK;
				box.x2 = (box.x2 + R300_CLIPRECT_OFFSET) &
					R300_CLIPRECT_MASK;
				box.y2 = (box.y2 + R300_CLIPRECT_OFFSET) &
					R300_CLIPRECT_MASK;
			}

			OUT_RING((box.x1 << R300_CLIPRECT_X_SHIFT) |
				 (box.y1 << R300_CLIPRECT_Y_SHIFT));
			OUT_RING((box.x2 << R300_CLIPRECT_X_SHIFT) |
				 (box.y2 << R300_CLIPRECT_Y_SHIFT));

		}

		OUT_RING_REG(R300_RE_CLIPRECT_CNTL, r300_cliprect_cntl[nr - 1]);


		OUT_RING(CP_PACKET0(R300_RE_SCISSORS_TL, 1));
		OUT_RING(0);
		OUT_RING(R300_SCISSORS_X_MASK | R300_SCISSORS_Y_MASK);
		ADVANCE_RING();
	} else {


		BEGIN_RING(2);
		OUT_RING_REG(R300_RE_CLIPRECT_CNTL, 0);
		ADVANCE_RING();
	}


	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	OUT_RING(R300_RB3D_DC_FLUSH);
	ADVANCE_RING();
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(RADEON_WAIT_UNTIL, 0));
	OUT_RING(RADEON_WAIT_3D_IDLECLEAN);
	ADVANCE_RING();

	dev_priv->track_flush |= RADEON_FLUSH_EMITED;

	return 0;
}
