parse_connection_string(const char *connstr, PQExpBuffer errorMessage,
						bool use_defaults)
{

	if (uri_prefix_length(connstr) != 0)
		return conninfo_uri_parse(connstr, errorMessage, use_defaults);


	return conninfo_parse(connstr, errorMessage, use_defaults);
}
