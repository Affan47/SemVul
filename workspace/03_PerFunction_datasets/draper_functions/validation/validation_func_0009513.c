setLayerVisibility(bool) {
	ViewLayerCheckBox * cb = qobject_cast<ViewLayerCheckBox *>(sender());
	if (cb == NULL) return;


	cb->viewLayer()->setIncludeChildLayers(false);
	cb->viewLayer()->action()->trigger();
	cb->viewLayer()->setIncludeChildLayers(true);
}
