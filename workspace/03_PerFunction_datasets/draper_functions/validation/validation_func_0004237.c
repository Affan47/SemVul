onTimeout(FXObject*,FXSelector,void*){

  flags|=FLAG_CALLBACK;
  dbus_timeout_handle(timeout);
  if (flags&FLAG_REMOVED) {
    delete this;
    fxmessage("}\n");
    return 1;
    }
  else {
    if (dbus_timeout_get_enabled(timeout) && dbus_timeout_get_interval(timeout)>0 && !FXApp::instance()->hasTimeout(this,ID_TIMEOUT)){
      FXApp::instance()->addTimeout(this,GMDBusTimeout::ID_TIMEOUT,TIME_MSEC(dbus_timeout_get_interval(timeout)));
      }
    }
  flags&=~FLAG_CALLBACK;

  return 1;
  }
