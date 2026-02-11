rv6xx_force_pcie_gen1(struct radeon_device *rdev)
{
	u32 tmp;
	int i;

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	tmp &= LC_GEN2_EN;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	tmp |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (!(RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & LC_CURRENT_DATA_RATE))
			break;
		udelay(1);
	}

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	tmp &= ~LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);
}
