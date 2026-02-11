to_cp1251(Glib::ustring str)
{
	return (Glib::convert(str, "WINDOWS-1251", "UTF-8")).c_str();
}
