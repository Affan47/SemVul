fileSave()
{
	if(INPUT_FILENAME_XML.isEmpty())
		return fileSaveAs();
	else{
		gt.rules.write(this, INPUT_FILENAME_XML);

		gt.rules.modified=true;
		setRulesUnmodifiedAndOtherThings(&gt.rules);

		setCurrentFile(INPUT_FILENAME_XML);

		statusBar()->showMessage(tr("File saved"), STATUS_BAR_MILLISECONDS);
		return true;
	}
}
