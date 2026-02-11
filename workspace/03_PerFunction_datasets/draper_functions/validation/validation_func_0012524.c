CanInsertPotentialSimpleKey() const
	{
		if(!m_simpleKeyAllowed)
			return false;

		return !ExistsActiveSimpleKey();
	}
