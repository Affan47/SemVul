readIdentifier (tokenInfo *const token, const int firstChar)
{
	vString *const name = token->name;
	int c = firstChar;
	boolean first = TRUE;

	initToken (token);


	if (isLanguage (Lang_cpp) && firstChar == '~')
	{
		vStringPut (name, c);
		c = skipToNonWhite ();
	}

	do
	{
		vStringPut (name, c);
		if (CollectingSignature)
		{
			if (!first)
				vStringPut (Signature, c);
			first = FALSE;
		}
		c = cppGetc ();
	} while (isident (c) || ((isLanguage (Lang_java) || isLanguage (Lang_csharp)) && (isHighChar (c) || c == '.')));
	vStringTerminate (name);
	cppUngetc (c);

	analyzeIdentifier (token);
}
