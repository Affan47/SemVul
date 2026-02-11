doLoadPrevious(MainWindow * sketchWindow) {


    FMessageBox messageBox(sketchWindow);
    messageBox.setWindowTitle(tr("Import files from previous version?"));
    messageBox.setText(tr("Do you want to import parts and bins that you have created with earlier versions of Fritzing?\n"));
    messageBox.setInformativeText(tr("\nNote: You can import them later using the \"Help\" > \"Import parts and bins "
									"from old version...\" menu action."));
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setWindowModality(Qt::WindowModal);
    messageBox.setButtonText(QMessageBox::Ok, tr("Import"));
    messageBox.setButtonText(QMessageBox::Cancel, tr("Do not import now"));
    QMessageBox::StandardButton answer = (QMessageBox::StandardButton) messageBox.exec();

    if(answer == QMessageBox::Ok) {
		 sketchWindow->importFilesFromPrevInstall();
    }
}
