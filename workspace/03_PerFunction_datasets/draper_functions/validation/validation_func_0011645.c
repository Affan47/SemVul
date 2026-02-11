getSavePath(const QString & initialValue, const QString & defaultExt, const QString & title, const QString & type)
{

    QString defaultSavePath = initialValue;
    if (defaultSavePath.isEmpty()) {
        defaultSavePath = ExportWizard::tr("Unnamed %1.%2").arg(QDate::currentDate().toString()).arg(defaultExt);
        if (App::settings->contains("Fotowall/ExportDir"))
            defaultSavePath.prepend(App::settings->value("Fotowall/ExportDir").toString() + QDir::separator());
    }


    QString saveFilePath = QFileDialog::getSaveFileName(0, title, defaultSavePath, type);
    if (!saveFilePath.isEmpty()) {
        App::settings->setValue("Fotowall/ExportDir", QFileInfo(saveFilePath).absolutePath());
        if (QFileInfo(saveFilePath).suffix().isEmpty())
            saveFilePath += "." + defaultExt;
    }
    return saveFilePath;
}
