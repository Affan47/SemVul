changeIcon( const char *cmd, const char *icon )
{
	if( !cmd || !*cmd ||
		!icon || !*icon )
		return;

	string data = cmd;

	data += ":";
	data += icon;

	Dock::send( ChangeIconMessage, data.c_str(), data.length() );
}
