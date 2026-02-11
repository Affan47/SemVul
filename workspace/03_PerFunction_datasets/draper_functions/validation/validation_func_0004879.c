has_feature(
	const std::string &feature,
	const std::string &version)
{
	if (CL_String::to_lower(feature) == "xml" && (version == "1.0" || version.empty()))
		return true;

	return false;
}
