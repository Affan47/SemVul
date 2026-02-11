CheckRuleExpression(GrcFont * pfont, GdlRenderer * prndr,
	std::vector<bool> & vfLb, std::vector<bool> & vfIns, std::vector<bool> & vfDel,
	bool fValue, bool fValueIsInputSlot)
{
	bool fOkay = m_pexpTest->CheckRuleExpression(pfont, prndr, vfLb, vfIns, vfDel,
		false, false);
	if (!m_pexpTrue->CheckRuleExpression(pfont, prndr, vfLb, vfIns, vfDel,
		fValue, fValueIsInputSlot))
	{
		fOkay = false;
	}
	if (!m_pexpFalse->CheckRuleExpression(pfont, prndr, vfLb, vfIns, vfDel,
		fValue, fValueIsInputSlot))
	{
		fOkay = false;
	}
	return fOkay;
}
