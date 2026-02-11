SetName (char const *name, char const *convention)
{
	if (!convention)
		convention = "Unknown";
	m_Names[convention] = name;
}
