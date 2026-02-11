emit_copy_option(PQExpBuffer query, const char *keyword, const char *option)
{
	appendPQExpBufferStr(query, keyword);
	if (option[0] == '\'' ||
		((option[0] == 'E' || option[0] == 'e') && option[1] == '\''))
		appendPQExpBufferStr(query, option);
	else
		appendStringLiteralConn(query, option, pset.db);
}
