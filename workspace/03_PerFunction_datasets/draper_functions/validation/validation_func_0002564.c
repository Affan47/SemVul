opa_speed_to_ib(u16 in)
{
	u16 out = 0;

	if (in & OPA_LINK_SPEED_25G)
		out |= IB_SPEED_EDR;
	if (in & OPA_LINK_SPEED_12_5G)
		out |= IB_SPEED_FDR;

	return out;
}
