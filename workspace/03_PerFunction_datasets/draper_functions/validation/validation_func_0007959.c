neb2_get_lod_scale(int objnum)
{
	ship *shipp;
	ship_info *sip;


	if ( (objnum < 0)
		|| (objnum >= MAX_OBJECTS)
		|| (Objects[objnum].type != OBJ_SHIP)
		|| (Objects[objnum].instance < 0)
		|| (Objects[objnum].instance >= MAX_SHIPS)) {
		return 1.0f;
	}
	shipp = &Ships[Objects[objnum].instance];
	sip = &Ship_info[shipp->ship_info_index];


	if (sip->flags & SIF_SMALL_SHIP) {
		return 1.8f;
	} else if (sip->flags & SIF_BIG_SHIP) {
		return 1.4f;
	}


	return 1.0f;
}
