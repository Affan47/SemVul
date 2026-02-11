rv6xx_enable_bif_dynamic_pcie_gen2(struct radeon_device *rdev,
					       bool enable)
{
	u32 tmp;

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
	if (enable)
		tmp |= LC_HW_VOLTAGE_IF_CONTROL(1);
	else
		tmp |= LC_HW_VOLTAGE_IF_CONTROL(0);
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);
}
