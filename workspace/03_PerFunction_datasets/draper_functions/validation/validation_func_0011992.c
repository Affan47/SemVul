s_typeChanged (GtkWidget * , AP_UnixDialog_Lists * me)
{
	if(me->dontUpdate())
		return;
  	me->setDirty();
	me->setListTypeFromWidget();
	me->fillUncustomizedValues();
	me->loadXPDataIntoLocal();
	me->previewExposed();
}
