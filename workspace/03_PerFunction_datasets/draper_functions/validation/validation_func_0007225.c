drc_append_save_volatiles(struct drccore *drc)
{
	if (drc->icountptr)
		_mov_m32abs_r32(drc->icountptr, REG_EBP);
	if (drc->pcptr)
		_mov_m32abs_r32(drc->pcptr, REG_EDI);
	if (drc->esiptr)
		_mov_m32abs_r32(drc->esiptr, REG_ESI);
}
