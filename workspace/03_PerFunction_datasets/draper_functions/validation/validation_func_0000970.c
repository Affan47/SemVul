operator<< (std::ostream &os, const Member &member)
{
	os << "Member ID: 0x" << hex << member.id
	   << "\n   Plugin Name: " << member.plugin_name;
	os << "\n   Friendly Name: ";
	if( member.friendly_name.size() )
		os << member.friendly_name;
	else
		os << "<not set>";
	return os;
}
