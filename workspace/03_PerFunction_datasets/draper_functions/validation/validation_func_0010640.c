closeEvent(QCloseEvent *event)
{
    LOG("Closing MainWindow");
    Core::ICore::instance()->requestSaveSettings();


    QString exfile = commandLine()->value(Core::CommandLine::CL_ExchangeOutFile).toString();
    if (!exfile.isEmpty()) {
        LOG(QString("Exchange File : %1 - %2")
            .arg(exfile)
            .arg(commandLine()->value(Core::CommandLine::CL_EMR_Name).toString()));
        QString format = commandLine()->value(Core::CommandLine::CL_ExchangeOutFileFormat).toString();
        QString tmp;

        QString extraData = d->getXmlExtraData();


        if (commandLine()->value(Core::CommandLine::CL_MedinTux).toBool() ||
            commandLine()->value(Core::CommandLine::CL_EMR_Name).toString().compare("medintux", Qt::CaseInsensitive) == 0) {
            if (format=="html_xml" || format=="html") {
                DrugsDB::PrescriptionPrinterJob job;
                job.readSettings();
                job.addXmlExtraData(extraData);
                job.setDrugsModel(drugModel());
                tmp = prescriptionPrinter().prescriptionToHtml(job);
                tmp.replace("font-weight:bold;", "font-weight:600;");
                Utils::saveStringToFile(tmp, exfile, Utils::Overwrite, Utils::DontWarnUser);
            } else if (format=="xml") {
                savePrescription(exfile);
            }
        } else {
            if (format=="html_xml" || format=="html") {
                DrugsDB::PrescriptionPrinterJob job;
                job.readSettings();
                job.addXmlExtraData(extraData);
                job.setDrugsModel(drugModel());
                tmp = prescriptionPrinter().prescriptionToHtml(job);
                Utils::saveStringToFile(tmp, exfile, Utils::Overwrite, Utils::DontWarnUser);
            } else if (format=="xml") {
                savePrescription(exfile);
            }
        }
    }

    Core::ICore::instance()->coreIsAboutToClose();
    writeSettings();
    event->accept();
}
