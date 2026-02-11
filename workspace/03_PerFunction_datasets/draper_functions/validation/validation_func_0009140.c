MemberStatus(long member_id,
				const std::string &plugin_name,
				const std::string &msg,
				bool error)
{
	if( error )
		cout << _C("ERROR: ");
	cout << msg << endl;
}
