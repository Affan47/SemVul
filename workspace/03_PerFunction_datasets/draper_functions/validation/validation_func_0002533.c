on_floatCB_stateChanged(int state)
{
	if (state == Qt::Checked) {
		inlineCB->setChecked(false);
		placementLE->setEnabled(true);
	} else
		placementLE->setEnabled(false);
}
