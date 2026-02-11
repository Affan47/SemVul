updatePopup()
{
	if (!dirty)
		return;

	if (!usesDropDown)
		qWarning("IconActionGroup does not support !usesDropDown yet");

	popup->clear();

	QList<QAction *> list = group->findChildren<QAction *>();
	foreach(QAction *action, list) {
		if (!group->psiIcon() && action->inherits("IconAction"))
			group->setIcon(((IconAction *)action)->icon());

		popup->addAction(action);
	}

	group->setMenu(popup);
	dirty = false;
}
