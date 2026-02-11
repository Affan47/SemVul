getSymbolNameByLocation(Location *loc)
{
	return loc ? (loc->label ? loc->label->name : NULL): NULL;
}
