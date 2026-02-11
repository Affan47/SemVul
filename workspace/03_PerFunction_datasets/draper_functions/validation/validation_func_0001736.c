set_sl_rr(OPL3 *chip,int slot,int v)
{
	OPL3_CH   *CH   = &chip->P_CH[slot/2];
	OPL3_SLOT *SLOT = &CH->SLOT[slot&1];

	SLOT->sl  = sl_tab[ v>>4 ];

	SLOT->rr  = (v&0x0f)? 16 + ((v&0x0f)<<2) : 0;
	SLOT->eg_sh_rr  = eg_rate_shift [SLOT->rr + SLOT->ksr ];
	SLOT->eg_m_rr   = (1<<SLOT->eg_sh_rr)-1;
	SLOT->eg_sel_rr = eg_rate_select[SLOT->rr + SLOT->ksr ];
}
