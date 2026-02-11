slotSkinChanged(int skinNum)
{
    kDebug() << "NewGameDialogImpl::slotSkinChanged "
              << skinNum << " ; " << skinCombo->currentText()
              << " ; " << m_newGameSetup->worlds()[skinCombo->currentText()]->name() << " ; "
              << m_newGameSetup->worlds()[skinCombo->currentText()]->description();
              skinDescLabel->setText(i18n(m_newGameSetup->worlds()[skinCombo->currentText()]->description().toUtf8().data()));
              skinSnapshotPixmap->setPixmap(m_newGameSetup->worlds()[skinCombo->currentText()]->snapshot());

    playersNumberEntry->setMinimum(2);
    playersNumberEntry->setMaximum(m_newGameSetup->worlds()[skinCombo->currentText()]->getNationalities().size());
    localPlayersNumberEntry->setMinimum(1);
    localPlayersNumberEntry->setMaximum(m_newGameSetup->worlds()[skinCombo->currentText()]->getNationalities().size()-1);
}
