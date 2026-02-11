incompatible_module_error(const char *libname,
						  const Pg_magic_struct *module_magic_data)
{
	StringInfoData details;


	if (magic_data.version != module_magic_data->version)
		ereport(ERROR,
				(errmsg("incompatible library \"%s\": version mismatch",
						libname),
			  errdetail("Server is version %d.%d, library is version %d.%d.",
						magic_data.version / 100,
						magic_data.version % 100,
						module_magic_data->version / 100,
						module_magic_data->version % 100)));


	initStringInfo(&details);

	if (module_magic_data->funcmaxargs != magic_data.funcmaxargs)
	{
		if (details.len)
			appendStringInfoChar(&details, '\n');
		appendStringInfo(&details,
						 _("Server has FUNC_MAX_ARGS = %d, library has %d."),
						 magic_data.funcmaxargs,
						 module_magic_data->funcmaxargs);
	}
	if (module_magic_data->indexmaxkeys != magic_data.indexmaxkeys)
	{
		if (details.len)
			appendStringInfoChar(&details, '\n');
		appendStringInfo(&details,
						 _("Server has INDEX_MAX_KEYS = %d, library has %d."),
						 magic_data.indexmaxkeys,
						 module_magic_data->indexmaxkeys);
	}
	if (module_magic_data->namedatalen != magic_data.namedatalen)
	{
		if (details.len)
			appendStringInfoChar(&details, '\n');
		appendStringInfo(&details,
						 _("Server has NAMEDATALEN = %d, library has %d."),
						 magic_data.namedatalen,
						 module_magic_data->namedatalen);
	}
	if (module_magic_data->float4byval != magic_data.float4byval)
	{
		if (details.len)
			appendStringInfoChar(&details, '\n');
		appendStringInfo(&details,
					   _("Server has FLOAT4PASSBYVAL = %s, library has %s."),
						 magic_data.float4byval ? "true" : "false",
						 module_magic_data->float4byval ? "true" : "false");
	}
	if (module_magic_data->float8byval != magic_data.float8byval)
	{
		if (details.len)
			appendStringInfoChar(&details, '\n');
		appendStringInfo(&details,
					   _("Server has FLOAT8PASSBYVAL = %s, library has %s."),
						 magic_data.float8byval ? "true" : "false",
						 module_magic_data->float8byval ? "true" : "false");
	}

	if (details.len == 0)
		appendStringInfo(&details,
			  _("Magic block has unexpected length or padding difference."));

	ereport(ERROR,
			(errmsg("incompatible library \"%s\": magic block mismatch",
					libname),
			 errdetail("%s", details.data)));
}
