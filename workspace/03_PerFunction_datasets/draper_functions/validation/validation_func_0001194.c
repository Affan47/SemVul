radeon_legacy_lvds_update(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t lvds_gen_cntl, lvds_pll_cntl, pixclks_cntl, disp_pwr_man;
	int panel_pwr_delay = 2000;
	bool is_mac = false;
	uint8_t backlight_level;
	DRM_DEBUG_KMS("\n");

	lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	backlight_level = (lvds_gen_cntl >> RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	if (radeon_encoder->enc_priv) {
		if (rdev->is_atom_bios) {
			struct radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			panel_pwr_delay = lvds->panel_pwr_delay;
			if (lvds->bl_dev)
				backlight_level = lvds->backlight_level;
		} else {
			struct radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			panel_pwr_delay = lvds->panel_pwr_delay;
			if (lvds->bl_dev)
				backlight_level = lvds->backlight_level;
		}
	}


	if ((rdev->mode_info.connector_table == CT_IBOOK) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_EXTERNAL) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_INTERNAL) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_VGA))
		is_mac = true;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		disp_pwr_man = RREG32(RADEON_DISP_PWR_MAN);
		disp_pwr_man |= RADEON_AUTO_PWRUP_EN;
		WREG32(RADEON_DISP_PWR_MAN, disp_pwr_man);
		lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
		lvds_pll_cntl |= RADEON_LVDS_PLL_EN;
		WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);
		mdelay(1);

		lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
		lvds_pll_cntl &= ~RADEON_LVDS_PLL_RESET;
		WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);

		lvds_gen_cntl &= ~(RADEON_LVDS_DISPLAY_DIS |
				   RADEON_LVDS_BL_MOD_LEVEL_MASK);
		lvds_gen_cntl |= (RADEON_LVDS_ON | RADEON_LVDS_EN |
				  RADEON_LVDS_DIGON | RADEON_LVDS_BLON |
				  (backlight_level << RADEON_LVDS_BL_MOD_LEVEL_SHIFT));
		if (is_mac)
			lvds_gen_cntl |= RADEON_LVDS_BL_MOD_EN;
		mdelay(panel_pwr_delay);
		WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		pixclks_cntl = RREG32_PLL(RADEON_PIXCLKS_CNTL);
		WREG32_PLL_P(RADEON_PIXCLKS_CNTL, 0, ~RADEON_PIXCLK_LVDS_ALWAYS_ONb);
		lvds_gen_cntl |= RADEON_LVDS_DISPLAY_DIS;
		if (is_mac) {
			lvds_gen_cntl &= ~RADEON_LVDS_BL_MOD_EN;
			WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
			lvds_gen_cntl &= ~(RADEON_LVDS_ON | RADEON_LVDS_EN);
		} else {
			WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
			lvds_gen_cntl &= ~(RADEON_LVDS_ON | RADEON_LVDS_BLON | RADEON_LVDS_EN | RADEON_LVDS_DIGON);
		}
		mdelay(panel_pwr_delay);
		WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
		WREG32_PLL(RADEON_PIXCLKS_CNTL, pixclks_cntl);
		mdelay(panel_pwr_delay);
		break;
	}

	if (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	else
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

}
