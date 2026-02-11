read_uint64_t(const std::string &section, const std::string &name, uint64_t defaultValue, bool failIfNotFound ) const
{
	string s = readString(section,name,format("%lu",(long unsigned int)defaultValue),failIfNotFound);
	return mrpt::system::os::_strtoull(s.c_str(),NULL, 0);
}
