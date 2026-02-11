deletePrimaryNotifier( )
{
  if (m_notifiers.isEmpty())
    return;

  SmartRangeNotifier* n = m_notifiers.first();
  removeNotifier(n);
  delete n;
}
