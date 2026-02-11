makeFortranTag (tokenInfo *const token, tagType tag)
{
	token->tag = tag;
	if (includeTag (token->tag))
	{
		const char *const name = vStringValue (token->string);
		tagEntryInfo e;

		initTagEntry (&e, name);

		if (token->tag == TAG_COMMON_BLOCK)
			e.lineNumberEntry = (boolean) (Option.locate != EX_PATTERN);

		e.lineNumber	= token->lineNumber;
		e.filePosition	= token->filePosition;
		e.isFileScope	= isFileScope (token->tag);
		e.kindName		= FortranKinds [token->tag].name;
		e.kind			= FortranKinds [token->tag].letter;
		e.truncateLine	= (boolean) (token->tag != TAG_LABEL);

		if (ancestorCount () > 0)
		{
			const tokenInfo* const scope = ancestorScope ();
			if (scope != NULL)
			{
				e.extensionFields.scope [0] = FortranKinds [scope->tag].name;
				e.extensionFields.scope [1] = vStringValue (scope->string);
			}
		}
		if (! insideInterface () || includeTag (TAG_INTERFACE))
			makeTagEntry (&e);
	}
}
