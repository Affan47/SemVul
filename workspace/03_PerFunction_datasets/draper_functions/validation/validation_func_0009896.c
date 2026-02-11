radeon_legacy_get_engine_clock(struct radeon_device *rdev)
{
	struct radeon_pll *spll = &rdev->clock.spll;
	uint32_t fb_div, ref_div, post_div, sclk;

	fb_div = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	fb_div = (fb_div >> RADEON_SPLL_FB_DIV_SHIFT) & RADEON_SPLL_FB_DIV_MASK;
	fb_div <<= 1;
	fb_div *= spll->reference_freq;

	ref_div =
	    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) & RADEON_M_SPLL_REF_DIV_MASK;

	if (ref_div == 0)
		return 0;

	sclk = fb_div / ref_div;

	post_div = RREG32_PLL(RADEON_SCLK_CNTL) & RADEON_SCLK_SRC_SEL_MASK;
	if (post_div == 2)
		sclk >>= 1;
	else if (post_div == 3)
		sclk >>= 2;
	else if (post_div == 4)
		sclk >>= 3;

	return sclk;
}
