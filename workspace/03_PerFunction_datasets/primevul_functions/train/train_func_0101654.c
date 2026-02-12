void ConnectDialogEdit::on_qleName_textEdited(const QString& name) {
	if (bCustomLabel) {


		if (name.simplified().isEmpty()) {
			bCustomLabel = false;
		}
	} else {

		bCustomLabel = true;
	}
}
