writeCtagsEntry (const tagEntryInfo *const tag)
{
	int length = fprintf (TagFile.fp, "%s\t%s\t",
		tag->name, tag->sourceFileName);

	if (tag->lineNumberEntry)
		length += writeLineNumberEntry (tag);
	else
		length += writePatternEntry (tag);

	if (includeExtensionFlags ())
		length += addExtensionFields (tag);

	length += fprintf (TagFile.fp, "\n");

	return length;
}
