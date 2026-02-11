sst_detect_ics(struct fb_info *info)
{
	struct sstfb_par *par = info->par;
	int m_clk0_1, m_clk0_7, m_clk1_b;
	int n_clk0_1, n_clk0_7, n_clk1_b;
	int i;

	for (i = 0; i<5; i++ ) {
		sst_dac_write(DACREG_ICS_PLLRMA, 0x1);
		m_clk0_1 = sst_dac_read(DACREG_ICS_PLLDATA);
		n_clk0_1 = sst_dac_read(DACREG_ICS_PLLDATA);
		sst_dac_write(DACREG_ICS_PLLRMA, 0x7);
		m_clk0_7 = sst_dac_read(DACREG_ICS_PLLDATA);
		n_clk0_7 = sst_dac_read(DACREG_ICS_PLLDATA);
		sst_dac_write(DACREG_ICS_PLLRMA, 0xb);
		m_clk1_b= sst_dac_read(DACREG_ICS_PLLDATA);
		n_clk1_b= sst_dac_read(DACREG_ICS_PLLDATA);
		f_ddprintk("m_clk0_1: %#x, m_clk0_7: %#x, m_clk1_b: %#x\n",
			m_clk0_1, m_clk0_7, m_clk1_b);
		f_ddprintk("n_clk0_1: %#x, n_clk0_7: %#x, n_clk1_b: %#x\n",
			n_clk0_1, n_clk0_7, n_clk1_b);
		if ((   m_clk0_1 == DACREG_ICS_PLL_CLK0_1_INI)
		    && (m_clk0_7 == DACREG_ICS_PLL_CLK0_7_INI)
		    && (m_clk1_b == DACREG_ICS_PLL_CLK1_B_INI)) {
			return 1;
		}
	}
	return 0;
}
