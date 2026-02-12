void ConnectDialogEdit::on_qleServer_textEdited(const QString& server) {

	if (!bCustomLabel) {
		qleName->setText(server);
	}
}
