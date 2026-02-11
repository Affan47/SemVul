updateClearButton()
	{
		ui->clearPushButton->setEnabled(mModel->rowCount() > 0);
	}
