scaled_div_max(struct bcm_clk_div *div)
{
	u32 reg_div;

	if (divider_is_fixed(div))
		return (u64)div->u.fixed;

	reg_div = ((u32)1 << div->u.s.width) - 1;

	return scaled_div_value(div, reg_div);
}
