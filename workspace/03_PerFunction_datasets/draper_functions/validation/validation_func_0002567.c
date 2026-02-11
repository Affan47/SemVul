setEventType2(EventType* ct)
{
  if (_eventType2 == ct) return false;
  _eventType2 = ct;

  QString longName = ct ? ct->longName() : tr("(Hidden)");

  _partSelection->setEventType2(_eventType2);
  _stackSelection->setEventType2(_eventType2);
  _functionSelection->setEventType2(_eventType2);
  _multiView->setEventType2(_eventType2);

  updateStatusBar();

  return true;
}
