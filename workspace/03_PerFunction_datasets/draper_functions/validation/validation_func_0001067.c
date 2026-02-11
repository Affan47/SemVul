flags_associate(unsigned char flag, unsigned int restrictflags, bool def, const char *name)
{
	if (chanacs_flags[flag].value && chanacs_flags[flag].value != 0xFFFFFFFF)
		return 0;

	chanacs_flags[flag].value = flags_find_slot();
	chanacs_flags[flag].restrictflags = restrictflags;
	chanacs_flags[flag].def = def;
	chanacs_flags[flag].name = name;

	update_chanacs_flags();

	return chanacs_flags[flag].value;
}
