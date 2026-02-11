showInfoDlg(bool addDontShowAgain)
{
	KMessageBox::information(parentWidget(),
			i18n("Course name: %1", holeInfo.name()) + QString("\n")
			+ i18n("Created by %1", holeInfo.author()) + QString("\n")
			+ i18n("%1 holes", highestHole),
			i18n("Course Information"),
			addDontShowAgain? holeInfo.name() + QString(" ") + holeInfo.author() : QString());
}
