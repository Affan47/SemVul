GetElectronegativity(GcuElectronegativity* en)
{
	Element* Elt = Table[en->Z];
	if (!Elt || !Elt->m_en.size ()) return false;
	if (!en->scale)
	{
		*en = *Elt->m_en[0];
		return true;
	}
	for (int i = 0; Elt->m_en[i]; i++)
		if (!strcmp(en->scale, Elt->m_en[i]->scale))
		{
			en->value = Elt->m_en[i]->value;
			return true;
		}

		return false;
}
