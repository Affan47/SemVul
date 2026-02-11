includeTag (const tagType type)
{
	boolean include;
	Assert (type != TAG_UNDEFINED);
	include = FortranKinds [(int) type].enabled;
	if (include && isFileScope (type))
		include = Option.include.fileScope;
	return include;
}
