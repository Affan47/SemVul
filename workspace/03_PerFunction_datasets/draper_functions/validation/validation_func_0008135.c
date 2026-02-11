widgetChanged()
{
    emit changed(d->_unmanagedWidgetChangeState || managedWidgetChangeState());
}
