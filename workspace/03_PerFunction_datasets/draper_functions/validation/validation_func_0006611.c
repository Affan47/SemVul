onUpdCopy(FXObject*sender,FXSelector,void*){
  if (trackSelected() && source)
    sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_ENABLE),NULL);
  else
    sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_DISABLE),NULL);
  return 1;
  }
