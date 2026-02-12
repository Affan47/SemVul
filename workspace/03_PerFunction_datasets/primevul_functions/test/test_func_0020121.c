static void ismt_submit_desc(struct ismt_priv *priv)
{
	uint fmhp;
	uint val;

	ismt_desc_dump(priv);
	ismt_gen_reg_dump(priv);
	ismt_mstr_reg_dump(priv);


	fmhp = ((priv->head + 1) % ISMT_DESC_ENTRIES) << 16;
	val = readl(priv->smba + ISMT_MSTR_MCTRL);
	writel((val & ~ISMT_MCTRL_FMHP) | fmhp,
	       priv->smba + ISMT_MSTR_MCTRL);


	val = readl(priv->smba + ISMT_MSTR_MCTRL);
	writel(val | ISMT_MCTRL_SS,
	       priv->smba + ISMT_MSTR_MCTRL);
}
