ContextSelectorItemAt(GrpLineAndFile & lnf, int irit,
	std::string staClassOrAt, int , std::string staAlias)
{
	g_errorList.AddError(3135, this,
		"Cannot specify a selector in the context");

	if (staClassOrAt == "@")
		return ContextItemAt(lnf, irit, "_", staAlias);
	else
		return ContextItemAt(lnf, irit, staClassOrAt, staAlias);
}
