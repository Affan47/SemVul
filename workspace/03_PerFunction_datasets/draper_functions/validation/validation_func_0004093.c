wilc_wlan_start(void)
{
	wilc_wlan_dev_t *p = &g_wlan;
	u32 reg = 0;
	int ret;
	u32 chipid;


	if (p->io_func.io_type == HIF_SDIO) {
		reg = 0;
		reg |= BIT(3);
	} else if (p->io_func.io_type == HIF_SPI) {
		reg = 1;
	}
	acquire_bus(ACQUIRE_ONLY);
	ret = p->hif_func.hif_write_reg(WILC_VMM_CORE_CFG, reg);
	if (!ret) {
		wilc_debug(N_ERR, "[wilc start]: fail write reg vmm_core_cfg...\n");
		release_bus(RELEASE_ONLY);

		ret = -5;
		return ret;
	}
	reg = 0;
#ifdef WILC_SDIO_IRQ_GPIO
	reg |= WILC_HAVE_SDIO_IRQ_GPIO;
#endif

#ifdef WILC_DISABLE_PMU
#else
	reg |= WILC_HAVE_USE_PMU;
#endif

#ifdef WILC_SLEEP_CLK_SRC_XO
	reg |= WILC_HAVE_SLEEP_CLK_SRC_XO;
#elif defined WILC_SLEEP_CLK_SRC_RTC
	reg |= WILC_HAVE_SLEEP_CLK_SRC_RTC;
#endif

#ifdef WILC_EXT_PA_INV_TX_RX
	reg |= WILC_HAVE_EXT_PA_INV_TX_RX;
#endif

	reg |= WILC_HAVE_LEGACY_RF_SETTINGS;


#ifdef XTAL_24
	reg |= WILC_HAVE_XTAL_24;
#endif


#ifdef DISABLE_WILC_UART
	reg |= WILC_HAVE_DISABLE_WILC_UART;
#endif

	ret = p->hif_func.hif_write_reg(WILC_GP_REG_1, reg);
	if (!ret) {
		wilc_debug(N_ERR, "[wilc start]: fail write WILC_GP_REG_1 ...\n");
		release_bus(RELEASE_ONLY);

		ret = -5;
		return ret;
	}


	p->hif_func.hif_sync_ext(NUM_INT_EXT);

	ret = p->hif_func.hif_read_reg(0x1000, &chipid);
	if (!ret) {
		wilc_debug(N_ERR, "[wilc start]: fail read reg 0x1000 ...\n");
		release_bus(RELEASE_ONLY);

		ret = -5;
		return ret;
	}


	p->hif_func.hif_read_reg(WILC_GLB_RESET_0, &reg);
	if ((reg & BIT(10)) == BIT(10)) {
		reg &= ~BIT(10);
		p->hif_func.hif_write_reg(WILC_GLB_RESET_0, reg);
		p->hif_func.hif_read_reg(WILC_GLB_RESET_0, &reg);
	}

	reg |= BIT(10);
	ret = p->hif_func.hif_write_reg(WILC_GLB_RESET_0, reg);
	p->hif_func.hif_read_reg(WILC_GLB_RESET_0, &reg);
	release_bus(RELEASE_ONLY);

	return (ret < 0) ? ret : 0;
}
