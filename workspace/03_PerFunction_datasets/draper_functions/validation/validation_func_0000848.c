slotViewStatusBar(bool toggle)
{
  slotStatusNormalMsg(QString(tr("Toggle statusbar...")));

  ASSERT_ENGAUGE(statusBar() != 0);
  statusBar()->setShown(toggle);

  DefaultSettings::instance().setViewStatusBar(toggle);

  slotStatusNormalMsg(QString(tr("Ready.")));
}
