exynos5440_tmu_control(struct platform_device *pdev, bool on)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);
	struct thermal_zone_device *tz = data->tzd;
	unsigned int con, interrupt_en;

	con = get_con_reg(data, readl(data->base + EXYNOS5440_TMU_S0_7_CTRL));

	if (on) {
		con |= (1 << EXYNOS_TMU_CORE_EN_SHIFT);
		interrupt_en =
			(of_thermal_is_trip_valid(tz, 3)
			 << EXYNOS5440_TMU_INTEN_RISE3_SHIFT) |
			(of_thermal_is_trip_valid(tz, 2)
			 << EXYNOS5440_TMU_INTEN_RISE2_SHIFT) |
			(of_thermal_is_trip_valid(tz, 1)
			 << EXYNOS5440_TMU_INTEN_RISE1_SHIFT) |
			(of_thermal_is_trip_valid(tz, 0)
			 << EXYNOS5440_TMU_INTEN_RISE0_SHIFT);
		interrupt_en |=
			interrupt_en << EXYNOS5440_TMU_INTEN_FALL0_SHIFT;
	} else {
		con &= ~(1 << EXYNOS_TMU_CORE_EN_SHIFT);
		interrupt_en = 0;
	}
	writel(interrupt_en, data->base + EXYNOS5440_TMU_S0_7_IRQEN);
	writel(con, data->base + EXYNOS5440_TMU_S0_7_CTRL);
}
