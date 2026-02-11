ProcessClassList(RefAST ast, RefAST * pastNext)
{
	if (ast->getType() == IDENT)
	{
		*pastNext = ast->getNextSibling();

		if (!*pastNext)
			return ast->getText();
		int nextNodeTyp = ast->getNextSibling()->getType();
		if (nextNodeTyp != IDENT && nextNodeTyp != LITERAL_glyphid &&
			nextNodeTyp != LITERAL_unicode && nextNodeTyp != LITERAL_codepoint &&
			nextNodeTyp != LITERAL_postscript && nextNodeTyp != LITERAL_pseudo)
		{
			return ast->getText().c_str();
		}
	}

	Symbol psymClass = SymbolTable()->AddAnonymousClassSymbol(LineAndFile(ast));

	std::string staClassName = psymClass->FullName();
	GdlGlyphClassDefn * pglfc = psymClass->GlyphClassDefnData();
	Assert(pglfc);
	pglfc->SetName(staClassName);
	m_prndr->AddGlyphClass(pglfc);

	int nodetyp;
	RefAST astGlyph = ast;
	while (astGlyph &&
		((nodetyp = astGlyph->getType()) == IDENT ||
			nodetyp == LITERAL_glyphid ||
			nodetyp == LITERAL_unicode || nodetyp == LITERAL_codepoint || nodetyp == ZuHex ||
			nodetyp == LITERAL_postscript || nodetyp == LITERAL_pseudo))
	{
		ProcessGlyphClassMember(astGlyph, pglfc, NULL);
		astGlyph = astGlyph->getNextSibling();
	}
	*pastNext = astGlyph;

	return staClassName;
}
