_findDialogInTable(XAP_Dialog_Id id, UT_sint32 * pIndex) const
{

	UT_return_val_if_fail(pIndex, false);

	for (UT_sint32 k=0; k < m_vec_dlg_table.getItemCount(); k++)
	{
		if (m_vec_dlg_table.getNthItem(k)->m_id == id)
		{
			*pIndex = k;
			return true;
		}
	}
	UT_DEBUGMSG(("Could not find a match for id %d \n",id));
	UT_ASSERT_HARMLESS(UT_NOT_IMPLEMENTED);
	return false;
}
