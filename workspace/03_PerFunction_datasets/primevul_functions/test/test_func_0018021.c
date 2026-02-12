void PlayerGeneric::restart(mp_uint32 startPosition, mp_uint32 startRow, bool resetMixer, const mp_ubyte* customPanningTable, bool playOneRowOnly)
{
	if (player)
		player->restart(startPosition, startRow, resetMixer, customPanningTable, playOneRowOnly);
}
