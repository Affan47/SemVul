get_standard_cd_unit (cd_standard_unit csu)
{
	int unitnum = get_standard_cd_unit2 (csu);
	if (unitnum < 0)
		return -1;
#ifdef RETROPLATFORM
	rp_cd_device_enable (unitnum, true);
#endif
	delayed[unitnum] = 0;
	if (currprefs.cdslots[unitnum].delayed) {
		delayed[unitnum] = PRE_INSERT_DELAY;
	}
	return unitnum;
}
