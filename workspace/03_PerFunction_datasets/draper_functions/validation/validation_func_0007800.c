slotSkinDescriptionEdited()
{
  if (m_onu == 0) return;
  kDebug() << m_skinDefWidget->descriptionTextEdit->toPlainText();
  m_onu->setDescription(m_skinDefWidget->descriptionTextEdit->toPlainText());
}
