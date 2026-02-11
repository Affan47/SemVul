rv6xx_enable_dynamic_pcie_gen2(struct radeon_device *rdev,
					   struct radeon_ps *new_ps,
					   bool enable)
{
	struct rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	if (enable) {
		rv6xx_enable_bif_dynamic_pcie_gen2(rdev, true);
		rv6xx_enable_pcie_gen2_support(rdev);
		r600_enable_dynamic_pcie_gen2(rdev, true);
	} else {
		if (!(new_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2))
			rv6xx_force_pcie_gen1(rdev);
		rv6xx_enable_bif_dynamic_pcie_gen2(rdev, false);
		r600_enable_dynamic_pcie_gen2(rdev, false);
	}
}
