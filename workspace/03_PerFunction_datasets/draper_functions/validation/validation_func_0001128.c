FixFeatureTestsInRules(GrcFont * pfont)
{
	for (size_t ipexp = 0; ipexp < m_vpexpConstraints.size(); ipexp++)
	{
		m_vpexpConstraints[ipexp]->FixFeatureTestsInRules(pfont);
		m_vpexpConstraints[ipexp]->LookupExpCheck(true);
	}

	for (size_t irit = 0; irit < m_vprit.size(); irit++)
	{
		m_vprit[irit]->FixFeatureTestsInRules(pfont);
	}
}
