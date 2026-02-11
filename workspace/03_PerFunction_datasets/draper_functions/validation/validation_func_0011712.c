gma_find_best_pll(const struct gma_limit_t *limit,
		       struct drm_crtc *crtc, int target, int refclk,
		       struct gma_clock_t *best_clock)
{
	struct drm_device *dev = crtc->dev;
	const struct gma_clock_funcs *clock_funcs =
						to_gma_crtc(crtc)->clock_funcs;
	struct gma_clock_t clock;
	int err = target;

	if (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS) &&
	    (REG_READ(LVDS) & LVDS_PORT_EN) != 0) {


		if ((REG_READ(LVDS) & LVDS_CLKB_POWER_MASK) ==
		    LVDS_CLKB_POWER_UP)
			clock.p2 = limit->p2.p2_fast;
		else
			clock.p2 = limit->p2.p2_slow;
	} else {
		if (target < limit->p2.dot_limit)
			clock.p2 = limit->p2.p2_slow;
		else
			clock.p2 = limit->p2.p2_fast;
	}

	memset(best_clock, 0, sizeof(*best_clock));


	for (clock.m1 = limit->m1.min; clock.m1 <= limit->m1.max; clock.m1++) {
		for (clock.m2 = limit->m2.min;
		     (clock.m2 < clock.m1 || clock.m1 == 0) &&
		      clock.m2 <= limit->m2.max; clock.m2++) {
			for (clock.n = limit->n.min;
			     clock.n <= limit->n.max; clock.n++) {
				for (clock.p1 = limit->p1.min;
				     clock.p1 <= limit->p1.max;
				     clock.p1++) {
					int this_err;

					clock_funcs->clock(refclk, &clock);

					if (!clock_funcs->pll_is_valid(crtc,
								limit, &clock))
						continue;

					this_err = abs(clock.dot - target);
					if (this_err < err) {
						*best_clock = clock;
						err = this_err;
					}
				}
			}
		}
	}

	return err != target;
}
