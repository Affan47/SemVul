jobComboChanged(int)
{
   if (jobCombo->currentText() == tr("Any")) {
      fileSetCombo->setCurrentIndex(fileSetCombo->findText(tr("Any"), Qt::MatchExactly));
      return;
   }
   job_defaults job_defs;


   job_defs.job_name = jobCombo->currentText();
   if (m_console->get_job_defaults(job_defs)) {
      fileSetCombo->setCurrentIndex(fileSetCombo->findText(job_defs.fileset_name, Qt::MatchExactly));
      clientCombo->setCurrentIndex(clientCombo->findText(job_defs.client_name, Qt::MatchExactly));
   }
}
