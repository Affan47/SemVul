_setCheckItemValue(tControl item, tCheckState value,
											tOperation op )
{
	UT_return_if_fail (item <= m_vecProperties.getItemCount());

	sControlData * pItem = _getPropertyItem (item);
	UT_return_if_fail (pItem);

	pItem->setData (value);

	if ((op == op_UICHANGE) || (op == op_SYNC))
		pItem->changed (true);


	if (op == op_UICHANGE)
		_syncControls(item);
}
