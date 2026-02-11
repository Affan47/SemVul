SelectUnit (GtkTreeModel *, GtkTreePath *, GtkTreeIter *iter, PrintSetupDlg *dlg)
{
	GtkUnit unit;
	gtk_tree_model_get (GTK_TREE_MODEL (dlg->m_UnitList), iter, 1, &unit, -1);
	if (unit == dlg->m_Printable->GetUnit ()) {
		gtk_combo_box_set_active_iter (dlg->m_UnitBox, iter);
		return true;
	}
	return false;
}
