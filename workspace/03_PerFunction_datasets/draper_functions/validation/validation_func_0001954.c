update()
{
#if !USE_FIXCOST
  TraceCallListCost::update();
#else

  if (!_dirty) return;

#if TRACE_DEBUG
  qDebug("update %s", qPrintable( fullName() ));
#endif


  if (_firstFixCallCost) {
    clear();
    FixCallCost* item;
    for (item = _firstFixCallCost; item; item = item->nextCostOfPartCall())
      item->addTo(this);
  }

  _dirty = false;

#if TRACE_DEBUG
  qDebug("   > %s", qPrintable(costString(0)));
#endif

#endif
}
