c_name (VALUE self)
{
	RbPlaylist *pl = NULL;

	Data_Get_Struct (self, RbPlaylist, pl);

	return pl->name_value;
}
