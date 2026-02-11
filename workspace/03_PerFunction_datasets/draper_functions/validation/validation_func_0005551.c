radeon_write_agp_location(drm_radeon_private_t *dev_priv, u32 agp_loc)
{

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770) {
		RADEON_WRITE(R700_MC_VM_AGP_BOT, agp_loc & 0xffff);
		RADEON_WRITE(R700_MC_VM_AGP_TOP, (agp_loc >> 16) & 0xffff);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600) {
		RADEON_WRITE(R600_MC_VM_AGP_BOT, agp_loc & 0xffff);
		RADEON_WRITE(R600_MC_VM_AGP_TOP, (agp_loc >> 16) & 0xffff);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV515)
		R500_WRITE_MCIND(RV515_MC_AGP_LOCATION, agp_loc);
	else if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
		 ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740))
		RS690_WRITE_MCIND(RS690_MC_AGP_LOCATION, agp_loc);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS600)
		RS600_WRITE_MCIND(RS600_MC_AGP_LOCATION, agp_loc);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) > CHIP_RV515)
		R500_WRITE_MCIND(R520_MC_AGP_LOCATION, agp_loc);
	else
		RADEON_WRITE(RADEON_MC_AGP_LOCATION, agp_loc);
}
