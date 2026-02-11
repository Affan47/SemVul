setSourceFileParameters (vString *const fileName, const langType language)
{
    if (File.source.name != NULL)
	vStringDelete (File.source.name);
    File.source.name = fileName;

    if (File.source.tagPath != NULL)
	eFree (File.source.tagPath);
    if (! Option.tagRelative || isAbsolutePath (vStringValue (fileName)))
	File.source.tagPath = eStrdup (vStringValue (fileName));
    else
	File.source.tagPath =
		relativeFilename (vStringValue (fileName), TagFile.directory);

    if (vStringLength (fileName) > TagFile.max.file)
	TagFile.max.file = vStringLength (fileName);

    File.source.isHeader = isIncludeFile (vStringValue (fileName));
    if (language != -1)
		File.source.language = language;
	else
		File.source.language = getFileLanguage (vStringValue (fileName));
}
