parseGeneralToken (statementInfo *const st, const int c)
{
	const tokenInfo *const prev = prevToken (st, 1);

	if (isident1 (c) || (isLanguage (Lang_java) && isHighChar (c)))
	{
		parseIdentifier (st, c);
		if (isType (st->context, TOKEN_NAME) &&
			isType (activeToken (st), TOKEN_NAME) && isType (prev, TOKEN_NAME))
		{
			initToken (st->context);
		}
	}
	else if (c == '.' || c == '-')
	{
		if (! st->assignment)
			st->notVariable = TRUE;
		if (c == '-')
		{
			int c2 = cppGetc ();
			if (c2 != '>')
				cppUngetc (c2);
		}
	}
	else if (c == '!' || c == '>')
	{
		int c2 = cppGetc ();
		if (c2 != '=')
			cppUngetc (c2);
	}
	else if (c == '@' && isLanguage (Lang_java))
	{
		parseJavaAnnotation (st);
	}
	else if (isExternCDecl (st, c))
	{
		st->declaration = DECL_NOMANGLE;
		st->scope = SCOPE_GLOBAL;
	}
}
