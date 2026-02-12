void ConnectDialogEdit::accept() {
	validate();
	if (bOk) {
		QString server = qleServer->text().simplified();


		const int schemaPos = server.indexOf(QLatin1String("://"));
		if (schemaPos != -1) {
			server.remove(0, schemaPos + 3);
		}

		const int pathPos = server.indexOf(QLatin1Char('/'));
		if (pathPos != -1) {
			server.resize(pathPos);
		}

		qleServer->setText(server);

		if (qleName->text().simplified().isEmpty() || !bCustomLabel) {
			qleName->setText(server);
		}

		QDialog::accept();
	}
}
