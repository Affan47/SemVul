ExplicitPseudos(PseudoSet & setpglf)
{
	for (size_t iglfc = 0; iglfc < m_vpglfc.size(); iglfc++)
		m_vpglfc[iglfc]->ExplicitPseudos(setpglf);
	return setpglf.size();
}
