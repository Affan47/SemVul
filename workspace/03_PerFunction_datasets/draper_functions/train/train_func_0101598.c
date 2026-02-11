GlyphAttrList(std::vector<Symbol> & vpsym)
{
	for (SymbolTableMap::iterator it = EntriesBegin();
		it != EntriesEnd();
		++it)
	{
		Symbol psym = it->second;


		if (psym->m_psymtblSubTable)
			psym->m_psymtblSubTable->GlyphAttrList(vpsym);

		else if (psym->IsGeneric() && psym->FitsSymbolType(ksymtGlyphAttr))
		{
			if (psym->InternalID() >= 0)
			{
				while (signed(vpsym.size()) <= psym->InternalID())
					vpsym.push_back(NULL);

				vpsym[psym->InternalID()] = psym;
			}
		}
	}
}
