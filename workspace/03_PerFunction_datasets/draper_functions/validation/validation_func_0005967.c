WalkFsmMachineClasses()
{
	FsmMachineClass * pfsmc;
	for (size_t i = 0; i < m_vpfsmc.size(); i++)
	{
		pfsmc = m_vpfsmc[i];
	}

	for (utf16 w = 0; w < kMaxTotalGlyphs; w++)
	{
		pfsmc = m_rgpfsmcAssignments[w];
	}
}
