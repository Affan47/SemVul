find_cip(DIVA_CAPI_ADAPTER *a, byte *bc, byte *hlc)
{
	word i;
	word j;

	for (i = 9; i && !ie_compare(bc, cip_bc[i][a->u_law]); i--);

	for (j = 16; j < 29 &&
		     (!ie_compare(bc, cip_bc[j][a->u_law]) || !ie_compare(hlc, cip_hlc[j])); j++);
	if (j == 29) return i;
	return j;
}
