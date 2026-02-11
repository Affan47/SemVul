GetResidue (char const *symbol, bool *ambiguous)
{
	map<string, SymbolResidue>::iterator i = m_Residues.find (symbol);
	if (i != m_Residues.end ()) {
		if (ambiguous)
			*ambiguous = (*i).second.ambiguous;
		return (*i).second.res;
	} else
		return gcu::Document::GetResidue (symbol, ambiguous);
}
