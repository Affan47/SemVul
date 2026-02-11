slotNationalitySelected(QListWidgetItem* item)
{
  kDebug();
  Nationality* nationality = m_onu->nationalityNamed(item->text());
  if (nationality != 0)
  {
    initNationalityWidgetWith(nationality);
  }
}
