createStatusBar()
{
	QStatusBar *status = statusBar();

	m_positionLabel = new QLabel(status);
	m_positionLabel->setMinimumWidth(150);
	status->addPermanentWidget(m_positionLabel, 0);

	status->showMessage(tr("Ready"));
}
